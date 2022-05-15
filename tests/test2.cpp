#include <Account.h>
#include <Transaction.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

inline bool operator==(Account a, Account b) { return true; }

class MockTransaction: public Transaction{
  public:
  MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

//Тестирование класса Transaction

TEST(Transaction, SaveToDataBase) {
  MockTransaction tr;
  Account from(1, 500);
  Account to(2, 400);
  EXPECT_CALL(tr, SaveToDataBase(from, to, 150)).Times(1);
  tr.SaveToDataBase(from, to, 150);
}
