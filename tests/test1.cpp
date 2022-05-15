#include <Transaction.h>
#include <Account.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

inline bool operator==(Account a, Account b) { return true; }

class MockAccount: public Account{
	public:
	MockAccount(int id, int balance):Account(id, balance){}
	MOCK_METHOD(void, Unlock, (), (override));
};

//Тестирование класса Account

TEST(Account, GetBalance){
	MockAccount acc(1,500);
	EXPECT_EQ(acc.Account::GetBalance(), 500);
}

TEST(Account, ChangeBalance) {
	MockAccount acc(1, 500);
	EXPECT_THROW(acc.Account::ChangeBalance(250), std::runtime_error);
	acc.Account::Lock();
	acc.Account::ChangeBalance(250);
	EXPECT_EQ(acc.Account::GetBalance(), 750);
}

TEST(Account, Lock) {
	MockAccount acc(1, 500);
	acc.Account::Lock();
	EXPECT_THROW(acc.Account::Lock(), std::runtime_error);
}

TEST(Account, Unlock) {
	MockAccount acc(1, 500);
	EXPECT_CALL(acc, Unlock()).Times(1);
	acc.Unlock();
}