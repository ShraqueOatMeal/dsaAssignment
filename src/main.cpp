#include "LinkList.h"
#include "radixSort.h"
#include "reviews.h"
#include "transactions.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// Declaration
void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList);
void loadTransaction(ifstream &transactionFile, transactions *transArray,
                     int size);
void displayTransactionArr(transactions *transArray, int size);

void loadReview(ifstream &reviewFile, LinkList<reviews> &reviewList);
void loadReview(ifstream &reviewFile, reviews *reviewArray, int size);
void displayReviewsArray(reviews *reviewArray, int size);

void linearSearch(int catChoice, int paymentChoice, int size,
                  transactions *transArray);

void linearSearch(int catChoice, int paymentChoice, int size,
                  LinkList<transactions> &transactionList);

int rowsNum(ifstream &file);

void calculatePercentage(LinkList<transactions> &transactionList, int size,
                         const string &category, const string &paymentMethod);

void calculatePercentage(transactions *transArray, int size,
                         const string &category, const string &paymentMethod);

// Use to trim the white spaces, tabs, and new lines from the string
string trim(const string &str) {
  size_t first = str.find_first_not_of(" \n\r\t");
  if (string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \n\r\t");
  return str.substr(first, (last - first + 1));
}

// Use to define the payment method
enum paymentMeth { BankTransfer = 1, PayPal, DebitCard, COD, CreditCard };

// Use to define the category
enum category {
  Automotive = 1,
  Books,
  Groceries,
  Sports,
  Toys,
  Beauty,
  Furniture,
  Electronics,
  Fashion,
  HomeAppliances
};

// System will run in here
int main(int argc, char *argv[]) {
  LinkList<reviews> reviewList;
  LinkList<transactions> transactionList;

  ifstream transactionFile("../../data/transactions_cleaned.csv");
  ifstream reviewFile("../../data/reviews_cleaned.csv");

  int choice;
  string mode;

  cout << "Choose a mode to run: " << endl;
  cout << "\t1. Link List" << endl;
  cout << "\t2. Array" << endl;
  cout << "Mode: ";
  cin >> choice;
  // loadReview(reviewFile, reviewList);

  // cout << "Display csv data from link list: " << endl;
  // reviewList.display();
  // transactionList.display();

  int transCount = rowsNum(transactionFile);
  int reviewCount = rowsNum(reviewFile);

  transactions *transArray = new transactions[transCount];
  reviews *reviewArray = new reviews[reviewCount];

  choice == 1 ? loadReview(reviewFile, reviewList),
      loadTransaction(transactionFile, transactionList)
              : loadReview(reviewFile, reviewArray, reviewCount),
      loadTransaction(transactionFile, transArray, transCount);

  // cout << "Display csv data from array: " << endl;
  // displayTransactionArr(transArray, transCount);
  // displayReviewsArray(reviewArray, reviewCount);

  choice == 1 ? radixSort::radixsort(&transactionList, transCount),
      radixSort::countSort(&reviewList, reviewCount)
              : radixSort::radixsort(transArray, transCount),
      radixSort::countSort(reviewArray, reviewCount);

  // Question 1: Array
  // displayTransactionArr(transArray, transCount);

  // Question 1: Link List
  // transactionList.display();

  // Question 2
  // filter transactions based on the category and payment method
  int catChoice;
  int paymentChoice;
  cout << "Choose a category to filter: " << endl;
  cout << "\t1. Automotive\n\t2. Books\n\t3. Groceries\n\t4. Sports\n\t5. "
          "Toys\n\t6. Beauty\n\t7. Furniture\n\t8. Electronics\n\t9. "
          "Fashion\n\t10. Home Appliances"
       << endl;
  cout << "Category: ";
  cin >> catChoice;

  cout << "Choose a payment method to filter: " << endl;
  cout << "\t1. Bank Transfer\n\t2. PayPal\n\t3. Debit Card\n\t4. Cash on "
          "Delivery\n\t5. "
          "Credit Card"
       << endl;
  cout << "Payment Method: ";
  cin >> paymentChoice;

  choice == 1
      ? linearSearch(catChoice, paymentChoice, transCount, transactionList)
      : linearSearch(catChoice, paymentChoice, transCount, transArray);
  cout << endl;

  // Question 3: which words are most frequently used in the reviews rated 1
  // star?

  int count = 0;

  for (int i = 0; i < reviewCount && reviewArray[i].rating == 1; i++) {
    // string review = reviewArray[i].review;
    count++;
  }
  string *words = new string[count];
  displayReviewsArray(reviewArray, count);

  // displayReviewsArray(reviewArray, reviewCount);

  return 0;
}

// Methods

// load link list
void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList) {

  string line;

  // Skip Header
  getline(transactionFile, line);

  while (getline(transactionFile, line)) {
    stringstream ss(line);
    string custID, prod, cat, priceStr, date, paymentMethod;
    getline(ss, custID, ',');
    getline(ss, prod, ',');
    getline(ss, cat, ',');
    getline(ss, priceStr, ',');
    getline(ss, date, ',');
    getline(ss, paymentMethod);

    transactions t;

    t.custID = custID;
    t.prod = prod;
    t.cat = cat;
    t.price = stod(priceStr);
    t.date = date;
    t.paymentMethod = trim(paymentMethod);

    transactionList.addData(t);
  }
}

// load array
void loadTransaction(ifstream &transactionFile, transactions *transArray,
                     int size) {

  string line;

  // Skip Header
  getline(transactionFile, line);

  int index = 0;

  while (getline(transactionFile, line) && index < size) {
    stringstream ss(line);
    string custID, prod, cat, priceStr, date, paymentMethod;
    getline(ss, custID, ',');
    getline(ss, prod, ',');
    getline(ss, cat, ',');
    getline(ss, priceStr, ',');
    getline(ss, date, ',');
    getline(ss, paymentMethod);

    transactions t;

    t.custID = custID;
    t.prod = prod;
    t.cat = cat;
    t.price = stod(priceStr);
    t.date = date;
    t.paymentMethod = trim(paymentMethod);

    transArray[index] = t;
    index++;
  }
}

// Use to display the transactions array
void displayTransactionArr(transactions *transArr, int size) {
  cout << "Transactions (Array):" << endl;
  for (int i = 0; i < size; i++) {
    transArr[i].print();
  }
}

// load link list
void loadReview(ifstream &reviewFile, LinkList<reviews> &reviewList) {
  string line;

  // Skip Header
  getline(reviewFile, line);

  // Read Reviews
  while (getline(reviewFile, line)) {
    stringstream ss(line);
    string prodID, custID, ratingStr, reviewText;

    getline(ss, prodID, ',');
    getline(ss, custID, ',');
    getline(ss, ratingStr, ',');
    getline(ss, reviewText);

    reviews r;

    r.prodID = prodID;
    r.custID = custID;
    r.rating = stoi(ratingStr);
    r.review = reviewText;

    reviewList.addData(r);
  }
}

void calculatePercentage(LinkList<transactions> &transactionList,
                         const string &category, const string &paymentMethod) {
  int categoryCount = 0;
  int matchCount = 0;

  Node<transactions> *current = transactionList.getHead();

  while (current != nullptr) {
    if (current->data.cat == category) {
      categoryCount++;
      if (current->data.paymentMethod == paymentMethod) {
        matchCount++;
      }
    }
    current = current->next;
  }

  double percentage =
      (categoryCount > 0) ? (double)matchCount / categoryCount * 100 : 0;
  cout << "Category: " << category << endl;
  cout << "Payment Method: " << paymentMethod << endl;
  cout << "Transactions in category: " << categoryCount << endl;
  cout << "Transactions with payment method: " << matchCount << endl;
  cout << "Percentage: " << fixed << setprecision(2) << percentage << "%"
       << endl;
}

// Use to filter the transactions based on the category and payment method
// using link list
void linearSearch(int catChoice, int paymentChoice, int size,
                  LinkList<transactions> &transactionList) {
  string selectedCat;
  string selectedPaymentMethod;

  switch (catChoice) {
  case Automotive:
    selectedCat = "Automotive";
    break;
  case Books:
    selectedCat = "Books";
    break;
  case Groceries:
    selectedCat = "Groceries";
    break;
  case Sports:
    selectedCat = "Sports";
    break;
  case Toys:
    selectedCat = "Toys";
    break;
  case Beauty:
    selectedCat = "Beauty";
    break;
  case Furniture:
    selectedCat = "Furniture";
    break;
  case Electronics:
    selectedCat = "Electronics";
    break;
  case Fashion:
    selectedCat = "Fashion";
    break;
  case HomeAppliances:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Unknown Category Choice" << endl;
    break;
  }

  switch (paymentChoice) {
  case BankTransfer:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case PayPal:
    selectedPaymentMethod = "PayPal";
    break;
  case DebitCard:
    selectedPaymentMethod = "Debit Card";
    break;
  case COD:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case CreditCard:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Unknown Payment Method Choice" << endl;
    break;
  }

  cout << "Filtered List: " << endl;

  Node<transactions> *current = transactionList.getHead();

  while (current != nullptr) {

    if (current->data.cat == selectedCat &&
        current->data.paymentMethod == selectedPaymentMethod) {
      current->data.print();
    }
    current = current->next;
  }

  calculatePercentage(transactionList, selectedCat, selectedPaymentMethod);
}

// load array
void loadReview(ifstream &reviewFile, reviews *reviewArray, int size) {
  string line;

  // Skip Header
  getline(reviewFile, line);

  int index = 0;

  // Read Reviews
  while (getline(reviewFile, line) && index < size) {
    stringstream ss(line);
    string prodID, custID, ratingStr, reviewText;

    getline(ss, prodID, ',');
    getline(ss, custID, ',');
    getline(ss, ratingStr, ',');
    getline(ss, reviewText);

    reviews r;

    r.prodID = prodID;
    r.custID = custID;
    r.rating = stoi(ratingStr);
    r.review = reviewText;

    reviewArray[index] = r;
    index++;
  }
}

// Use to display the reviews array
void displayReviewsArray(reviews *reviewArray, int size) {
  cout << "Reviews (Array):" << endl;
  for (int i = 0; i < size; i++) {
    reviewArray[i].print();
  }
}

void calculatePercentage(transactions *transArray, int size,
                         const string &category, const string &paymentMethod) {
  int categoryCount = 0;
  int matchCount = 0;

  for (int i = 0; i < size; i++) {
    if (transArray[i].cat == category) {
      categoryCount++;
      if (transArray[i].paymentMethod == paymentMethod) {
        matchCount++;
      }
    }
  }

  double percentage =
      (categoryCount > 0) ? (double)matchCount / categoryCount * 100 : 0;
  cout << "Category: " << category << endl;
  cout << "Payment Method: " << paymentMethod << endl;
  cout << "Transactions in category: " << categoryCount << endl;
  cout << "Transactions with payment method: " << matchCount << endl;
  cout << "Percentage: " << fixed << setprecision(2) << percentage << "%"
       << endl;
}

// Use to filter the transactions based on the category and payment method
// using array
void linearSearch(int catChoice, int paymentChoice, int size,
                  transactions *transArray) {
  string selectedCat;
  string selectedPaymentMethod;

  switch (catChoice) {
  case Automotive:
    selectedCat = "Automotive";
    break;
  case Books:
    selectedCat = "Books";
    break;
  case Groceries:
    selectedCat = "Groceries";
    break;
  case Sports:
    selectedCat = "Sports";
    break;
  case Toys:
    selectedCat = "Toys";
    break;
  case Beauty:
    selectedCat = "Beauty";
    break;
  case Furniture:
    selectedCat = "Furniture";
    break;
  case Electronics:
    selectedCat = "Electronics";
    break;
  case Fashion:
    selectedCat = "Fashion";
    break;
  case HomeAppliances:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Unknown Category Choice" << endl;
    break;
  }

  switch (paymentChoice) {
  case BankTransfer:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case PayPal:
    selectedPaymentMethod = "PayPal";
    break;
  case DebitCard:
    selectedPaymentMethod = "Debit Card";
    break;
  case COD:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case CreditCard:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Unknown Payment Method Choice" << endl;
    break;
  }

  cout << "Filtered List: " << endl;
  for (int i = 0; i < size; i++) {
    if (transArray[i].cat == selectedCat &&
        transArray[i].paymentMethod == selectedPaymentMethod) {
      transArray[i].print();
    }
  }

  calculatePercentage(transArray, size, selectedCat, selectedPaymentMethod);
}

// Use to count the number of rows in the file
int rowsNum(ifstream &file) {
  int count = 0;
  string line;

  getline(file, line);

  while (getline(file, line)) {
    if (!line.empty()) {
      count++;
    }
  }

  file.clear();
  file.seekg(0);
  return count;
}
