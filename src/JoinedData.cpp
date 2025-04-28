#include "JoinedData.h"
#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"

JoinedData::JoinedData() {
  // Constructor implementation
}

JoinedData::~JoinedData() {
  // Destructor implementation
}

void JoinedData::innerJoinLists(LinkList<transactions> &transactionList,
                                LinkList<reviews> &reviewList,
                                LinkList<mergedData> &joinedList) {
  Node<transactions> *transCurrent = transactionList.getHead();

  while (transCurrent != nullptr) {
    Node<reviews> *reviewCurrent = reviewList.getHead();

    while (reviewCurrent != nullptr) {
      if (transCurrent->data.custID == reviewCurrent->data.custID) {
        mergedData joinedRecord;

        // Copy transaction data
        joinedRecord.custID = transCurrent->data.custID;
        joinedRecord.prod = transCurrent->data.prod;
        joinedRecord.cat = transCurrent->data.cat;
        joinedRecord.price = transCurrent->data.price;
        joinedRecord.date = transCurrent->data.date;
        joinedRecord.paymentMethod = transCurrent->data.paymentMethod;

        // Copy review data
        joinedRecord.prodID = reviewCurrent->data.prodID;
        joinedRecord.rating = reviewCurrent->data.rating;
        joinedRecord.review = reviewCurrent->data.review;

        joinedList.addData(joinedRecord);
      }
      reviewCurrent = reviewCurrent->next;
    }
    transCurrent = transCurrent->next;
  }
}

void JoinedData::innerJoinArrays(transactions *transArray, int transCount,
                                 reviews *reviewArray, int reviewCount,
                                 mergedData *mergedArray, int mergedCount) {
  mergedCount = 0;

  for (int i = 0; i < transCount; i++) {
    for (int j = 0; j < reviewCount; j++) {
      if (transArray[i].custID == reviewArray[j].custID) {
        // Copy transaction data
        mergedArray[mergedCount].custID = transArray[i].custID;
        mergedArray[mergedCount].prod = transArray[i].prod;
        mergedArray[mergedCount].cat = transArray[i].cat;
        mergedArray[mergedCount].price = transArray[i].price;
        mergedArray[mergedCount].date = transArray[i].date;
        mergedArray[mergedCount].paymentMethod = transArray[i].paymentMethod;

        // Copy review data
        mergedArray[mergedCount].prodID = reviewArray[j].prodID;
        mergedArray[mergedCount].rating = reviewArray[j].rating;
        mergedArray[mergedCount].review = reviewArray[j].review;

        mergedCount++;
      }
    }
  }
}
