#include <iostream>
#include <vector>
using namespace std;

class Order;
class Granted;
class Cancelled;
class NewOrder;
class Invoiced;
class Registered;

struct Product
{
    string name;
    double price;
};

// ------------------- states -------------------
class OrderState
{
private:

    void OperationIsNotAllowed(string operationName)
    {
        cout << "Operation " << operationName << " is not allowed for Order's state!\n";
    }

protected:
    string stateName;
    Order* order;

public:
    OrderState(Order* order)
    {
        this->order = order;
    }
    string GetName() const
    {
        return stateName;
    }

    virtual void AddProduct()
    {
        OperationIsNotAllowed("Add Product");
    }
    virtual void Register()
    {
        OperationIsNotAllowed("Add Product");
    }
    virtual void Grant()
    {
        OperationIsNotAllowed("Grant");
    }
    virtual void Ship()
    {
        OperationIsNotAllowed("Ship");
    }
    virtual void Invoice()
    {
        OperationIsNotAllowed("Invoice");
    }
    virtual void Cancel()
    {
        OperationIsNotAllowed("Cancel");
    }
};

class Order
{
private:
    OrderState* state;
    vector<Product> products;

public:
    Order()
    {
        //state = new NewOrder(this);
    }
    void SetOrderState(OrderState* state)
    {
        this->state = state;
    }
    void WriteCurrentStateName()
    {
        cout << "Current Order's state: " << state->GetName() << endl;
    }

    void AddProduct(Product product)
    {
        products.push_back(product);
        state->AddProduct();
    }
    void Register()
    {
        state->Register();
    }
    void Grant()
    {
        state->Grant();
    }
    void Ship()
    {
        state->Ship();
    }
    void Invoice()
    {
        state->Invoice();
    }
    void Cancel()
    {
        state->Cancel();
    }

    void DoShipping()
    {
        cout << "Shipping..." << endl;
    }
    void DoAddProduct()
    {
        cout << "Adding product..." << endl;
    }
    void DoCancel()
    {
        cout << "Cancelation..." << endl;
    }
    void DoGrant()
    {
        cout << "Granting..." << endl;
    }
    void DoRegister()
    {
        cout << "Registration..." << endl;
    }
    void DoInvoice()
    {
        cout << "Invoicing..." << endl;
    }
};

class Cancelled : public OrderState
{
public:
    Cancelled(Order* order) : OrderState(order)
    {
        stateName = "Cancelled";
    }
};
class Invoiced : public OrderState
{
public:
    Invoiced(Order* order) : OrderState(order)
    {
        stateName = "Invoiced";
    }
};
class Shipped : public OrderState
{
public:
    Shipped(Order* order) : OrderState(order)
    {
        stateName = "Shipped";
    }

    void Invoice() override
    {
        order->DoInvoice();
        order->SetOrderState(new Invoiced(order));
    }
};
class Granted : public OrderState
{
public:
    Granted(Order* order) : OrderState(order)
    {
        stateName = "Granted";
    }
    void AddProduct() override
    {
        order->DoAddProduct();
    }
    void Ship() override
    {
        order->DoShipping();
        order->SetOrderState(new Shipped(order));
    }
    void Cancel() override
    {
        order->DoCancel();
        order->SetOrderState(new Cancelled(order));
    }
};
class Registered : public OrderState
{
public:
    Registered(Order* order) : OrderState(order)
    {
        stateName = "Registered";
    }

    void AddProduct() override
    {
        order->DoAddProduct();
    }
    void Grant() override
    {
        order->DoGrant();
        order->SetOrderState(new Granted(order));
    }
    void Cancel() override
    {
        order->DoCancel();
        order->SetOrderState(new Cancelled(order));
    }
};
class NewOrder : public OrderState
{
public:
    NewOrder(Order* order) : OrderState(order)
    {
        stateName = "NewOrder";
    }

    void AddProduct() override
    {
        order->DoAddProduct();
    }
    void Register() override
    {
        order->DoRegister();
        order->SetOrderState(new Registered(order));
    }
    void Cancel() override
    {
        order->DoCancel();
        order->SetOrderState(new Cancelled(order));
    }
};

int main()
{
    Product beer;
    beer.name = "Lvivske 1715";
    beer.price = 26;

    Order order;
    order.SetOrderState(new NewOrder(&order)); // initial state

    order.WriteCurrentStateName();

    order.AddProduct(beer);
    order.WriteCurrentStateName();

    order.Register();
    order.WriteCurrentStateName();

    // can not invoice the order until shipped
    order.Invoice();
    order.WriteCurrentStateName();

    order.Grant();
    order.WriteCurrentStateName();

    //order.Cancel();
    //order.WriteCurrentStateName();

    order.Ship();
    order.WriteCurrentStateName();

    order.AddProduct(beer);
    order.WriteCurrentStateName();

    order.Invoice();
    order.WriteCurrentStateName();
}