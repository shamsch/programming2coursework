#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards() : top_(nullptr)
{
}

Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data *item_to_be_released = top_;
        top_ = top_->next;

        delete item_to_be_released;
    }
}

void Cards::add(int id)
{
    Card_data *ptr = new Card_data();
    ptr->data = id;
    ptr->next = top_;
    top_ = ptr;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data *item_to_be_printed = top_;
    int running_number = 1;

    while (item_to_be_printed != nullptr)
    {
        s << running_number << ": " << item_to_be_printed->data << std::endl;
        ++running_number;
        item_to_be_printed = item_to_be_printed->next;
    }
}

bool Cards::remove(int &id)
{
    if (top_ != nullptr)
    {
        id=top_->data;
        top_=top_->next;
        return true;
    }
    return false;
}

bool Cards::bottom_to_top()
{
    if (top_ != nullptr || top_->next != nullptr)
    {
        Card_data *lastElement = top_;
        Card_data *secondToLast = nullptr;

        while (lastElement->next != nullptr)
        {
            secondToLast = lastElement;
            lastElement = lastElement->next;
        }

        secondToLast->next = nullptr;
        lastElement->next = top_;
        top_ = lastElement;

        return true;
    }
    else
    {
        return false;
    }
}

bool Cards::top_to_bottom()
{
    if (top_ != nullptr || top_->next != nullptr)
    {
        Card_data *firstElement = top_;
        Card_data *lastElement = top_;

        while (lastElement->next != nullptr)
        {
            lastElement = lastElement->next;
        }

        top_ = firstElement->next;
        lastElement->next = firstElement;
        firstElement->next = nullptr;

        return true;
    }
    else
    {
        return false;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    static int count = 1;
    if (top != NULL)
    {
        recursive_print(top->next, s);
        s << count << ": " << top->data << std::endl;
        ++count;
        return 1;
    }
    return 0;
}
