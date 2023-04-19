#include <vector>
#include <iostream>
using namespace std;

#include "Cursor.h"
#include "unit_test_framework.h"

TEST(CursorDefaultConstructor) {
    Cursor cursor;
    ASSERT_EQUAL(cursor.getLineN(), 0);
    ASSERT_EQUAL(cursor.getCharN(), 0);
}

TEST(CursorParameterizedConstructor) {
    Cursor cursor(2, 3);
    ASSERT_EQUAL(cursor.getLineN(), 2);
    ASSERT_EQUAL(cursor.getCharN(), 3);
}

TEST(CursorMoveUpDown) {
    Cursor cursor(1, 1);
    cursor.moveUp();
    ASSERT_EQUAL(cursor.getLineN(), 0);
    ASSERT_EQUAL(cursor.getCharN(), 1);
    cursor.moveDown();
    ASSERT_EQUAL(cursor.getLineN(), 1);
    ASSERT_EQUAL(cursor.getCharN(), 1);
}

TEST(CursorMoveLeftRight) {
    Cursor cursor(1, 1);
    cursor.moveLeft();
    ASSERT_EQUAL(cursor.getLineN(), 1);
    ASSERT_EQUAL(cursor.getCharN(), 0);
    cursor.moveRight();
    ASSERT_EQUAL(cursor.getLineN(), 1);
    ASSERT_EQUAL(cursor.getCharN(), 1);
}

TEST(CursorNextLine) {
    Cursor cursor(1, 3);
    cursor.nextLine();
    ASSERT_EQUAL(cursor.getLineN(), 2);
    ASSERT_EQUAL(cursor.getCharN(), 0);
}

TEST(CursorSetPosition) {
    Cursor cursor;
    cursor.setPosition(2, 4);
    ASSERT_EQUAL(cursor.getLineN(), 2);
    ASSERT_EQUAL(cursor.getCharN(), 4);
}

TEST(CursorMaxCharN) {
    Cursor cursor(2, 4);
    cursor.setMaxCharNReached(3);
    ASSERT_EQUAL(cursor.getMaxCharNReached(), 3);
}

TEST(CursorMoveDownUpToMaxCharN) {
    Cursor cursor(2, 4);
    cursor.setMaxCharNReached(3);
    cursor.moveDownToMaxCharN();
    ASSERT_EQUAL(cursor.getLineN(), 3);
    ASSERT_EQUAL(cursor.getCharN(), 3);
    cursor.moveUpToMaxCharN();
    ASSERT_EQUAL(cursor.getLineN(), 2);
    ASSERT_EQUAL(cursor.getCharN(), 3);
}

TEST_MAIN()
