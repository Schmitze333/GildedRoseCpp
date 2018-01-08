#include "gmock/gmock.h"
#include "GildedRose.h"

using ::testing::Eq;

class NormalItem : public ::testing::Test 
{
public:
  GildedRose gildedRose;
  int initialSellIn{ 5 };
  int initialQuality{ 10 };

  void NormalItemWithSellInAndQuality() {
    gildedRose.addItem(Item("NORMAL ITEM", initialSellIn, initialQuality));
  }

  void HasSellInDecreaseOf1() {
    HasSellInOf(initialSellIn - 1);
  }

  void HasSellInOf(const int newSellIn) {
    ASSERT_THAT(gildedRose.getItem(0).sellIn, Eq(newSellIn));
  }

  void HasQualityOf(const int newQuality) {
    ASSERT_THAT(gildedRose.getItem(0).quality, Eq(newQuality));
  }
};

TEST_F(NormalItem, BeforeSellDate) {
  NormalItemWithSellInAndQuality();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 1);
}

TEST_F(NormalItem, OnSellDate) {
  initialSellIn = 0;
  NormalItemWithSellInAndQuality();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, AfterSellDate) {
  initialSellIn = -10;
  NormalItemWithSellInAndQuality();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, OfZeroQuality) {
  initialQuality = 0;
  NormalItemWithSellInAndQuality();

  gildedRose.updateQuality();

  HasQualityOf(0);
}
