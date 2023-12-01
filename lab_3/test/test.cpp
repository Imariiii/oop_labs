#include "hexagon.h"
#include "octagon.h"
#include "triangle.h"
#include "array.h"
#include "generator.h"
#include <gtest/gtest.h>

TEST(PointConstructorDefault, test_0) {
    Point p1;
    ASSERT_TRUE(p1.getX() == 0 && p1.getY() == 0);
}

TEST(PointConstructorByCoordinates, test_0) {
    Point p1(1, 2);
    ASSERT_TRUE(fabs(p1.getX() - 1) < EPSILON && fabs(p1.getY() - 2)< EPSILON);
}

TEST(PointConstructorByCoordinates, test_1) {
    Point p1(-10.3, 12.4);
    ASSERT_TRUE(fabs(p1.getX() - (-10.3)) < EPSILON && fabs(p1.getY() - 12.4) < EPSILON);
}

TEST(PointConstructorByCoordinates, test_2) {
    Point p1(17.1123, -56.489);
    ASSERT_TRUE(fabs(p1.getX() - 17.1123) < EPSILON && fabs(p1.getY() - (-56.489)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_0) {
    Point p1(Point(3,4));
    ASSERT_TRUE(fabs(p1.getX() - 3) < EPSILON && fabs(p1.getY() - 4) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_1) {
    Point p1(Point(-10,-0.123112));
    ASSERT_TRUE(fabs(p1.getX() - (-10)) < EPSILON && fabs(p1.getY() - (-0.123112)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_2) {
    Point p1(Point(0,0));
    ASSERT_TRUE(fabs(p1.getX()) < EPSILON && fabs(p1.getY()) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_3) {
    Point p1(Point(Point(4.1231, 313.109283)));
    ASSERT_TRUE(fabs(p1.getX() - 4.1231) < EPSILON && fabs(p1.getY() - 313.109283) < EPSILON);
}

TEST(PointEqualOperatorCheck_test_3_Test, test_0) {
    ASSERT_TRUE(Point(3,4) == Point(3,4));
}

TEST(PointEqualOperator, test_1) {
    ASSERT_TRUE(Point(3,5) != Point(3,4));
}

TEST(PointEqualOperator, test_2) {
    ASSERT_TRUE(Point(1.012, 0) != Point(1.1, 0));
}

TEST(PointDistance, test_0) {
    Point p1(-9,2), p2(-10,-100);
    ASSERT_TRUE(fabs(p1.distance(p2) - 102.00) < EPSILON);
}

TEST(PointDistance, test_1) {
    Point p1(4,5), p2(8,0);
    ASSERT_TRUE(fabs(p1.distance(p2) - 6.40) < EPSILON);
}

TEST(PointDistance, test_2) {
    Point p1(12.3,-10.55), p2(-1.89,0.78);
    ASSERT_FALSE(fabs(p1.distance(p2) - 23.00) < EPSILON);
}

TEST(OperatorCopy, test_0) {
    Point p1(12.3,-10.55), p2;
    p2 = p1;
    ASSERT_TRUE(p2 == p1);
}

TEST(TriangleVectorConstructor, test0) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(TriangleVectorConstructor, test1) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(TriangleVectorConstructor, test2) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(TriangleVectorConstructor, test3) {
    ASSERT_NO_THROW(Triangle t(GenerateFigures(3)));
}

TEST(TriangleCopyConstructor, test0) {
    Triangle t(GenerateFigures(3));
    Triangle t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleMoveConstructor, test0) {
    Triangle t(GenerateFigures(3));
    Triangle t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(TriangleSquare, test0) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(fabs(double(t) - 3.2111) < EPSILON);
}

TEST(TriangleSquare, test1) {
    Triangle t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(TriangleAverage, test0) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t.getCenter() == Point(1.83, 2.28));
}

TEST(TriangleAverage, test1) {
    Triangle t(std::vector<Point>{Point(-7.55,-3.16), Point(-5.63,-4.58), Point(-5.36, -2.21)});
    ASSERT_TRUE(t.getCenter() == Point(-6.18,-3.31));
}

TEST(TriangleAverage, test2) {
    Triangle t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(TriangleOperatorMove, test0) {
    Triangle t(GenerateFigures(3)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleOperatorCopy, test0) {
    Triangle t(GenerateFigures(3)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(HexagonVectorConstructor, test0) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(HexagonVectorConstructor, test1) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(HexagonVectorConstructor, test2) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(HexagonVectorConstructor, test3) {
    ASSERT_NO_THROW(Hexagon t(GenerateFigures(6)));
}

TEST(HexagonCopyConstructor, test0) {
    Hexagon t(GenerateFigures(6));
    Hexagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonMoveConstructor, test0) {
    Hexagon t(GenerateFigures(6));
    Hexagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(HexagonSquare, test0) {
    Hexagon t(std::vector<Point> {Point(-2,9), Point(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(fabs(double(t) - 1252.27) < EPSILON);
}

TEST(HexagonSquare, test1) {
    Hexagon t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(HexagonAverage, test0) {
    Hexagon t(std::vector<Point> {Point(-2,9), Point(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(t.getCenter() == Point(19.95, 9.03));
}

TEST(HexagonAverage, test1) {
    Hexagon t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(HexagonOperatorMove, test0) {
    Hexagon t(GenerateFigures(6)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonOperatorCopy, test0) {
    Hexagon t(GenerateFigures(6)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(OctagonVectorConstructor, test0) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(OctagonVectorConstructor, test1) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(OctagonVectorConstructor, test2) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(OctagonVectorConstructor, test3) {
    ASSERT_NO_THROW(Octagon t(GenerateFigures(8)));
}

TEST(OctagonCopyConstructor, test0) {
    Octagon t(GenerateFigures(8));
    Octagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonMoveConstructor, test0) {
    Octagon t(GenerateFigures(8));
    Octagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(OctagonSquare, test0) {
    Octagon t(std::vector<Point> {Point(-5,0), Point(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(double(t) - 1023.63 < EPSILON);
}

TEST(OctagonSquare, test1) {
    Octagon t1;
    ASSERT_THROW((double) t1, std::range_error);
}

TEST(OctagonAverage, test0) {
    Octagon t(std::vector<Point> {Point(-5,0), Point(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(t.getCenter() == Point(6.83, 14.9));
}

TEST(OctagonAverage, test1) {
    Octagon t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(OctagonOperatorMove, test0) {
    Octagon t(GenerateFigures(8)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonOperatorCopy, test0) {
    Octagon t(GenerateFigures(8)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(ArrayInitListConstructor, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar({&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar.getArr()[0] != o1) 
        f = false;
    if (*ar.getArr()[1] != o2) 
        f = false;
    if (*ar.getArr()[2] != h1) 
        f = false;
    if (*ar.getArr()[3] != t1) 
        f = false;
    ASSERT_TRUE(f);
}

TEST(ArrayVectorConstructor, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar.getArr()[0] != o1) 
        f = false;
    if (*ar.getArr()[1] != o2) 
        f = false;
    if (*ar.getArr()[2] != h1) 
        f = false;
    if (*ar.getArr()[3] != t1) 
        f = false;
    ASSERT_TRUE(f);
}

TEST(ArraySumSquare, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ASSERT_TRUE(fabs(double(ar) - (double(o1) + double(o2) + double(h1) + double(t1))) < EPSILON);
}

TEST(ArraySumSquare, test1) {
    FigureArray ar;
    ASSERT_THROW((double) ar, std::range_error);
}

TEST(ArrayPushBack, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ar.push_back(&h2);
    ASSERT_TRUE(*ar.getArr()[ar.getSize() - 1] == h2);
}

TEST(ArrayPopBack, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ar.pop_back();
    ASSERT_TRUE(ar.getSize() == 3 && *ar.getArr()[ar.getSize() - 1] == h1);
}

TEST(ArrayPopBack, test1) {
    FigureArray ar;
    ASSERT_THROW(ar.pop_back(), std::range_error);
}

TEST(ArrayErase, test0) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    bool f = true;
    ar.erase(2);
    if (*ar.getArr()[0] != o1) 
        f = false;
    if (*ar.getArr()[1] != o2) 
        f = false;
    if (*ar.getArr()[2] != t1) 
        f = false;
    ASSERT_TRUE(ar.getSize() == 3 && f);
}

TEST(ArrayErase, test1) {
    FigureArray ar;
    ASSERT_THROW(ar.erase(1), std::range_error);
}

TEST(ArrayErase, test2) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ASSERT_THROW(ar.erase(10), std::range_error);
}

TEST(FiguresEqualTest, test0) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    Triangle t1(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test1) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Triangle t1(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test2) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Hexagon h(GenerateFigures(6));
    ASSERT_FALSE(t == h);
}

TEST(FiguresEqualTest, test3) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Octagon o(GenerateFigures(8));
    ASSERT_FALSE(t == o);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
