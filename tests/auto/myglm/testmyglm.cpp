#include <QtTest>
#include "myglm.h"

class TestMyGLM : public QObject
{
    Q_OBJECT
public:
    TestMyGLM();
    ~TestMyGLM();    
private slots:
    void initTestCase();
    void testcase1();
    void cleanUpTestCase();
};

TestMyGLM::TestMyGLM(){

}

TestMyGLM::~TestMyGLM(){

}

void TestMyGLM::testcase1(){
    readglm("/home/marco/TestData/VTC_N-40_RFX_ZT_AR-2_ITHR-100.glm");
}

void TestMyGLM::initTestCase(){

}

void TestMyGLM::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMyGLM)

#include "testmyglm.moc"
