#include <gtest/gtest.h>

#include "core/Exception.h"
#include "core/AutoResource.h"

namespace prismTest {

class AutoResourceTestObject {
    
public:
    AutoResourceTestObject() 
        : a(0), b(0)
    {}

    AutoResourceTestObject(int a, int b)
        : a(a), b(b)
    {}

    ~AutoResourceTestObject() {
        a -= 3;
        b -= 3;
    }

    const int getA() {return a;}
    const int getB() {return b;}
    void setA(int a) {this->a = a;}
    void setB(int b) {this->b = b;}

private:
    int a;
    int b;
};

using AutoIntPointer = prism::AutoResource<int*>;
using AutoInt = prism::AutoResource<int>;
using AutoObjPointer = prism::AutoResource<AutoResourceTestObject*>;
using AutoObj = prism::AutoResource<AutoResourceTestObject>;


void intDeleter(int value) {
    --value;
}

void intPtrDeleter(int *value) {
    --*value;
}

void newObjDestructor(AutoResourceTestObject* obj) {
    delete obj;
    obj = nullptr;
}

void objPtrDestructor(AutoResourceTestObject* obj) {
    obj->setA(obj->getA() - 999);
    obj->setB(obj->getB() - 999);
}

void objDestructor(AutoResourceTestObject obj) {
    obj.setA(obj.getA() - 999);
    obj.setB(obj.getB() - 999);
}


TEST(autoResourceTests, intPointerResourceTest) {
    int x = 1000;

    // no compilation allowed with invalid types (nullptr, NULL) as resource.
    // AutoIntPointer inv1{nullptr, nullptr};
    // AutoIntPointer inv2{nullptr, NULL};
    // AutoIntPointer inv3{NULL, NULL};
    // AutoIntPointer inv4{nullptr, intPtrDeleter};
    // AutoIntPointer inv5{NULL, intPtrDeleter};


    // scope
    {
        AutoIntPointer a{};
        AutoIntPointer b{&x, nullptr};
        AutoIntPointer c{&x, NULL};
        AutoIntPointer d{&x, intPtrDeleter};

        ASSERT_FALSE(a);
        ASSERT_TRUE(b);
        ASSERT_TRUE(c);
        ASSERT_TRUE(d);
        EXPECT_THROW({
            try {
                a.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);
        ASSERT_EQ(b.get(), &x);
        ASSERT_EQ(c.get(), &x);
        ASSERT_EQ(d.get(), &x);

        *b = 10001;
        ASSERT_EQ(*b.get(), 10001);
        ASSERT_EQ(*c.get(), 10001);
        ASSERT_EQ(*d.get(), 10001);
        ASSERT_EQ(x, 10001);
    }
    // intPtrDeleter should have been called once (by d) decremeting value
    ASSERT_EQ(x, 10000);
}

TEST(autoResourceTests, objResourceTest) {
    AutoResourceTestObject x(5, 5);

    // scope
    {
        AutoObjPointer a{};
        AutoObjPointer b{&x, nullptr};
        AutoObjPointer c{&x, NULL};
        AutoObjPointer d{&x, objPtrDestructor};

        ASSERT_FALSE(a);
        ASSERT_TRUE(b);
        ASSERT_TRUE(c);
        ASSERT_TRUE(d);
        EXPECT_THROW({
            try {
                a.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);
        ASSERT_EQ(b.get(), &x);
        ASSERT_EQ(c.get(), &x);
        ASSERT_EQ(d.get(), &x);
        ASSERT_EQ(d->getA(), 5);
        d->setA(7);
        ASSERT_EQ(b->getA(), 7);
        ASSERT_EQ(c->getA(), 7);
        ASSERT_EQ(b->getB(), 5);
        ASSERT_EQ(x.getA(), 7);
        ASSERT_EQ(x.getB(), 5);
    }
    // objPtrDestructor should have been called once (by d) subtracting 999 from A and B
    ASSERT_EQ(x.getA(), 7 - 999);
    ASSERT_EQ(x.getB(), 5 - 999);
    
}

TEST(autoResourceTests, newObjTest) {
    AutoResourceTestObject* x = new AutoResourceTestObject(10, 10);

    // scope
    {
        AutoObjPointer a(x, newObjDestructor);

        ASSERT_EQ(a->getA(), 10);
        ASSERT_EQ(a->getB(), 10);
        a->setA(20);
        a->setB(20);
        ASSERT_EQ(a->getA(), 20);
        ASSERT_EQ(a->getB(), 20);

        // test move constructor
        AutoObjPointer b = std::move(a);
        ASSERT_EQ(b->getA(), 20);
        ASSERT_EQ(b->getB(), 20);
        ASSERT_FALSE(a); // a should now hold nothing in resource and destructor
        EXPECT_THROW({
            try {
                a.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);
        ASSERT_TRUE(b);

        // test cast operator
        AutoResourceTestObject* x1 = (AutoResourceTestObject*)b;
        ASSERT_EQ(x1, x);
        ASSERT_EQ(x1->getA(), 20);
        ASSERT_EQ(x1->getB(), 20);
        b->setA(30);
        b->setB(30);
        ASSERT_EQ(x1->getA(), 30);
        ASSERT_EQ(x1->getB(), 30);

        // test address operator
        ASSERT_EQ(x, *(&b));

        // test move assignment
        AutoObjPointer c;
        c = std::move(a);
        ASSERT_FALSE(c); // c should still hold nothing in resource and destructor since a holds nothing
        EXPECT_THROW({
            try {
                c.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);
        c = std::move(b);
        ASSERT_TRUE(c);
        ASSERT_EQ(c.get(), x);
        ASSERT_FALSE(a);
        EXPECT_THROW({
            try {
                a.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);
        ASSERT_FALSE(b); // b should now hold nothing in resource and destructor since moved to c
        EXPECT_THROW({
            try {
                b.get();
            } catch (const prism::Exception& e) {
                EXPECT_STREQ("AutoResource does not contain valid resource: cannot return resource", e.what());
                throw;
            }
        }, prism::Exception);

        // copy constructor disabled:
        // AutoObjPointer d(c);

        // reassignment disabled:
        // c = b;
    }
    // no real way to check x was deleted
    ASSERT_NE(x->getA(), 27);
    ASSERT_NE(x->getB(), 27);
}

TEST(autoResourceTests, objTest) {
    AutoResourceTestObject x = AutoResourceTestObject(10, 10);

    {
        AutoObjPointer a(&x, objPtrDestructor);
        AutoObjPointer b{&x, objPtrDestructor};
        AutoObjPointer c = AutoObjPointer(&x, objPtrDestructor);
        ASSERT_TRUE(a);
        ASSERT_TRUE(b);
        ASSERT_TRUE(c);

        a->setA(200);
        a->setB(400);
        ASSERT_EQ(a->getA(), 200);
        ASSERT_EQ(a->getB(), 400);
        ASSERT_EQ(b->getA(), 200);
        ASSERT_EQ(b->getB(), 400);
        ASSERT_EQ(c->getA(), 200);
        ASSERT_EQ(c->getB(), 400);
    }
    // destructor called on a, b, c should change x
    ASSERT_EQ(x.getA(), -2797);
    ASSERT_EQ(x.getB(), -2597);

    {
        // copies x, not reference
        AutoObj a(x, objDestructor);
        AutoObj b{x, objDestructor};
        AutoObj c = AutoObj(x, objDestructor);
        ASSERT_TRUE(a);
        ASSERT_TRUE(b);
        ASSERT_TRUE(c);
        ASSERT_EQ(a.get().getA(), -2797);
        ASSERT_EQ(a.get().getB(), -2597);
        ASSERT_EQ(b.get().getA(), -2797);
        ASSERT_EQ(b.get().getB(), -2597);
        ASSERT_EQ(c.get().getA(), -2797);
        ASSERT_EQ(c.get().getB(), -2597);

        ASSERT_NE(&x, &a);
        ASSERT_NE(&x, &b);
        ASSERT_NE(&x, &c);
        ASSERT_NE(&a, &b);
        ASSERT_NE(&b, &c);
        ASSERT_NE(&a, &c);
        (&a)->setA(200);
        (&a)->setB(400);
        ASSERT_EQ(a.get().getA(), 200);
        ASSERT_EQ(a.get().getB(), 400);
        ASSERT_EQ(b.get().getA(), -2797);
        ASSERT_EQ(b.get().getB(), -2597);
        ASSERT_EQ(c.get().getA(), -2797);
        ASSERT_EQ(c.get().getB(), -2597);

    }
    // destructor called on a, b, c should NOT change x
    ASSERT_EQ(x.getA(), -2797);
    ASSERT_EQ(x.getB(), -2597);
    
}

TEST(autoResourceTests, staticCastTest) {
    int x = 1;

    AutoInt a{x, intDeleter};
    ASSERT_EQ(a.get(), x);
    ASSERT_EQ(static_cast<int>(a), x);
    ASSERT_TRUE(a);

    AutoIntPointer b{&x, intPtrDeleter};
    ASSERT_EQ(b.get(), &x);
    ASSERT_EQ(static_cast<int *>(b), &x);
    ASSERT_TRUE(b);
}

TEST(autoResourceTests, lambdaDestructorTest) {
    AutoResourceTestObject x(5, 5);

    // scope
    {
        AutoObjPointer a {
            &x, 
            [](AutoResourceTestObject* b) {
                b->setA(-7); 
                b->setB(-9); 
            }
        };
    }
    ASSERT_EQ(x.getA(), -7);
    ASSERT_EQ(x.getB(), -9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}

