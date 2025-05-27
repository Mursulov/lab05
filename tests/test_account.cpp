#include <gtest/gtest.h>
#include "Account.hpp"

TEST(AccountTest, InitialBalance) {
    Account acc(100.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DepositIncreasesBalance) {
    Account acc(50.0);
    acc.deposit(25.5);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 75.5);
}

TEST(AccountTest, WithdrawDecreasesBalance) {
    Account acc(80.0);
    acc.withdraw(30.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 50.0);
}

TEST(AccountTest, MultipleOperations) {
    Account acc(0.0);
    acc.deposit(10.0);
    acc.withdraw(3.0);
    acc.deposit(7.5);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 14.5);
}