#include "gmock/gmock.h"
#include "GildedRose.h"

using ::testing::Eq;

class ItemFixture : public ::testing::Test
{
public:
  GildedRose gildedRose;
  int initialSellIn{ 5 };
  int initialQuality{ 10 };

  void MakeItem(const std::string name) {
    gildedRose.addItem(Item(name, initialSellIn, initialQuality));
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

class NormalItem : public ItemFixture
{
public:
  void MakeNormalItem() { MakeItem("NORMAL ITEM"); }
};

class AgedBrie : public ItemFixture
{
public:
  void MakeAgedBrie() { MakeItem("Aged Brie"); }
};

TEST_F(NormalItem, BeforeSellDate) {
  MakeNormalItem();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 1);
}

TEST_F(NormalItem, OnSellDate) {
  initialSellIn = 0;
  MakeNormalItem();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, AfterSellDate) {
  initialSellIn = -10;
  MakeNormalItem();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, OfZeroQuality) {
  initialQuality = 0;
  MakeNormalItem();

  gildedRose.updateQuality();

  HasQualityOf(0);
}

TEST_F(AgedBrie, BeforeSellDate) {
  MakeAgedBrie();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 1);
}

TEST_F(AgedBrie, BeforeSellDateWithMaxQuality) {
  initialQuality = 50;
  MakeAgedBrie();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(AgedBrie, OnSellDate) {
  initialSellIn = 0;
  MakeAgedBrie();

  gildedRose.updateQuality();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality  + 2);
}



// REFACTOR gildedRose.updateQuality to Subject();
