#include <gtest/gtest.h>
#include "Transaction.hpp"


TEST(TransactionTest, TransferMovesMoney) {
    Account from(200.0);
    Account to(50.0);
    Transaction::transfer(from, to, 75.0);
    EXPECT_DOUBLE_EQ(from.getBalance(), 125.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 125.0);
}

TEST(TransactionTest, TransferZeroAmount) {
    Account from(100.0);
    Account to(100.0);
    Transaction::transfer(from, to, 0.0);
    EXPECT_DOUBLE_EQ(from.getBalance(), 100.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 100.0);
}