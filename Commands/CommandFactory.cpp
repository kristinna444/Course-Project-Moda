#include "CommandFactory.h"

#include "RegisterCommand.h"
#include "LoginCommand.h" 
#include "AddItemCommand.h"
#include "RemoveItemCommand.h"
#include "CheckBalanceCommand.h"
#include "RedeemCommand.h"
#include "ListProductsCommand.h"
#include "ViewProductCommand.h"
#include "AddToCartCommand.h"
#include "RemoveFromCartCommand.h"
#include "ApplyDiscountCommand.h"
#include "RemoveDiscountCommand.h"
#include "ViewCartCommand.h"
#include "CheckoutCommand.h"
#include "ListShippedOrdersCommand.h"
#include "ConfirmOrderCommand.h"
#include "RateProductCommand.h"
#include "OrderHistoryCommand.h"
#include "RequestRefundCommand.h"
#include "RefundedOrdersCommand.h"
#include "ListPendingOrdersCommand.h"
#include "ApproveOrderCommand.h"
#include "RejectOrderCommand.h"
#include "ListOrdersCommand.h"
#include "ListBestSellingProductsCommand.h"
#include "ViewRevenueCommand.h"
#include "ListRefundsCommand.h"
#include "ApproveRefundCommand.h"
#include "RejectRefundCommand.h"
#include "SendCheckCommand.h"
#include "LogoutCommand.h"

Command* CommandFactory::create(const char* input)
{
	if (strcmp(input, "register") == 0) {
		return new RegisterCommand();
	}
	else if (strcmp(input, "login") == 0) {
		return new LoginCommand();
	}
	else if (strcmp(input, "add_item") == 0) {
		MyString name, description; 
		double price; 
		size_t quantity;

		std::cin >> name;
		std::cin >> price >> quantity;
		std::cin >> description;

		return new AddItemCommand(name, price, quantity, description);
	}
	else if (strcmp(input, "remove_item") == 0) {
		MyString name; 
		std::cin >> name;
		return new RemoveItemCommand(name); 
	}
	else if (strcmp(input, "check_balance") == 0) {
		return new CheckBalanceCommand();
	}
	else if (strcmp(input, "redeem") == 0) {
		MyString code;
		std::cin >> code; 
		return new RedeemCommand(code); 
	}
	else if (strcmp(input, "list_products") == 0) {
		return new ListProductsCommand(); 
	}
	else if (strcmp(input, "view_product") == 0) {
		int productID; 
		std::cin >> productID;
		std::cin.ignore(); 
		return new ViewProductCommand(productID); 
	}
	else if (strcmp(input, "add_to_cart") == 0) {
		int ID;
		size_t quantity;
		std::cin >> ID >> quantity;
		std::cin.ignore();
		return new AddToCartCommand(ID, quantity); 
	}
	else if (strcmp(input, "remove_from_cart") == 0) {
		MyString name;
		size_t quantity; 
		std::cin >> name;
		std::cin >> quantity;
		std::cin.ignore();
		return new RemoveFromCartCommand(name, quantity); 
	}
	else if (strcmp(input, "apply_discount") == 0) {
		return new ApplyDiscountCommand();
	}
	else if (strcmp(input, "remove_discount") == 0) {
		return new RemoveDiscountCommand();
	}
	else if (strcmp(input, "view_cart") == 0) {
		return new ViewCartCommand();
	}
	else if (strcmp(input, "checkout") == 0) {
		return new CheckoutCommand();
	}
	else if (strcmp(input, "list_shipped_orders") == 0) {
		return new ListShippedOrdersCommand();
	}
	else if (strcmp(input, "confirm_order") == 0) {
		size_t index;
		std::cin >> index; 
		std::cin.ignore();
		return new ConfirmOrderCommand(index); 
	}
	else if (strcmp(input, "rate_product") == 0) {
		int productID;
		double rating;
		std::cin >> productID >> rating;
		std::cin.ignore();
		return new RateProductCommand(productID, rating); 
	}
	else if (strcmp(input, "order_history") == 0) {
		return new OrderHistoryCommand();
	}
	else if (strcmp(input, "request_refund") == 0) {
		return new RequestRefundCommand();
	}
	else if (strcmp(input, "refunded_orders") == 0) {
		return new RefundedOrdersCommand();
	}
	else if (strcmp(input, "list_pending_orders") == 0) {
		return new ListPendingOrdersCommand();
	}
	else if (strcmp(input, "approve_order") == 0) {
		size_t index;
		std::cin >> index;
		std::cin.ignore(); 
		return new ApproveOrderCommand(index); 
	}
	else if (strcmp(input, "reject_order") == 0) {
		MyString desc;
		size_t index;
		std::cin >> desc;
		std::cin >> index;
		std::cin.ignore();
		return new RejectOrderCommand(index, desc); 
	}
	else if (strcmp(input, "list_orders") == 0) {
		return new ListOrdersCommand();
	}
	else if (strcmp(input, "list_best_selling_products") == 0) {
		return new ListBestSellingProductsCommand();
	}
	else if (strcmp(input, "view_revenue") == 0) {
		return new ViewRevenueCommand();
	}
	else if (strcmp(input, "list_refunds") == 0) {
		return new ListRefundsCommand();
	}
	else if (strcmp(input, "approve_refund") == 0) {
		size_t index;
		std::cin >> index;
		std::cin.ignore();
		return new ApproveRefundCommand(index); 
	}
	else if (strcmp(input, "reject_refund") == 0) {
		MyString desc;
		int ID;
		std::cin >> desc;
		std::cin >> ID;
		std::cin.ignore();
		return new RejectRefundCommand(ID, desc); 
	}
	else if (strcmp(input, "send_check")==0) {
		MyString EGN, code;
		double amount;

		std::cin >> EGN;
		std::cin >> code;
		std::cin >> amount;
		std::cin.ignore();
		return new SendCheckCommand(amount, code, EGN); 
	}
	else if (strcmp(input, "logout") == 0) {
		return new LogoutCommand();
	}

	throw std::logic_error("Invalid command");
}