#include "gmock/gmock.h"
#include "GildedRose.h"

using ::testing::Eq;

class NormalItem : public ::testing::Test 
{
public:
  GildedRose gildedRose;
  int initialSellIn{ 5 };
  int initialQuality{ 10 };

  void NormalItemWithSellInAndQuality(const int sellIn, const int quality) {
    gildedRose.addItem(Item("NORMAL ITEM", sellIn, quality));
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
  NormalItemWithSellInAndQuality(initialSellIn, initialQuality);

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 1);
}

TEST_F(NormalItem, OnSellDate) {
  NormalItemWithSellInAndQuality(0, initialQuality);

  gildedRose.updateQuality();

  HasSellInOf( -1 );
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, AfterSellDate) {
  NormalItemWithSellInAndQuality(-10, initialQuality);

  gildedRose.updateQuality();

  HasSellInOf( -11 );
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, OfZeroQuality) {
  NormalItemWithSellInAndQuality(initialSellIn, 0);

  gildedRose.updateQuality();

  HasQualityOf(0);
}
