#include "CItem.h"

/*

    int m_Code;
    string m_Description;
    double m_Price;
    double m_DiscountRate;

*/

CItem::CItem()
{

    m_Code = 0;
    m_Description = "";
    m_Price = 0.0;
    m_DiscountRate = 0.0;


}


CItem::CItem(int code, string description)
{

    m_Code = code;
    m_Description = description;
    m_Price = 0.0;
    m_DiscountRate = 0.0;

}
CItem::CItem(int code, string description, double price, double discountRate)
{
    m_Code = code;
    m_Description = description;
    m_Price = price;
    m_DiscountRate = discountRate;

}

void CItem::SetPrice(double price)
{
    m_Price = price;
}

void CItem::SetDiscountRate(double discountRate)
{
    m_DiscountRate = discountRate;
}

int CItem::GetCode(void)
{
    return m_Code;
}

string CItem::GetDescription(void)
{
    return m_Description;
}

double CItem::GetPrice(void)
{
    return m_Price;
}

double CItem::GetDiscountRate(void)
{
    return m_DiscountRate;
}

bool CItem::HasCode(int searchCode)
{
    return searchCode == m_Code;
}


void CItem::Display(void)
{
    cout << "Item Code " << m_Code << endl;
    cout << "Item Description " << m_Description << endl;
    cout << "Item Price " << m_Price << endl;
    cout << "Item Discount Rate " << m_DiscountRate << endl;
}

double CItem::GetDiscount(void)
{
    return m_Price * m_DiscountRate;
}