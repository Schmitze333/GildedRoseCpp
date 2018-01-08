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

  void Subject() { gildedRose.updateQuality(); }
};

class NormalItem : public ItemFixture
{
public:
  void MakeNormalItem() { MakeItem("NORMAL ITEM"); }
};

TEST_F(NormalItem, BeforeSellDate) {
  MakeNormalItem();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 1);
}

TEST_F(NormalItem, OnSellDate) {
  initialSellIn = 0;
  MakeNormalItem();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, AfterSellDate) {
  initialSellIn = -10;
  MakeNormalItem();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItem, OfZeroQuality) {
  initialQuality = 0;
  MakeNormalItem();

  Subject();

  HasQualityOf(0);
}

class AgedBrie : public ItemFixture
{
public:
  void MakeAgedBrie() { MakeItem("Aged Brie"); }
};

TEST_F(AgedBrie, BeforeSellDate) {
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 1);
}

TEST_F(AgedBrie, BeforeSellDateWithMaxQuality) {
  initialQuality = 50;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(AgedBrie, OnSellDate) {
  initialSellIn = 0;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(AgedBrie, OnSellDateNearMaxQuality) {
  initialSellIn = 0;
  initialQuality = 49;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

TEST_F(AgedBrie, OnSellDateWithMaxQuality) {
  initialSellIn = 0;
  initialQuality = 50;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

TEST_F(AgedBrie, AfterSellDate) {
  initialSellIn = -10;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(AgedBrie, AfterSellDateWithMaxQuality) {
  initialSellIn = -10;
  initialQuality = 50;
  MakeAgedBrie();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

class Sulfuras : public ItemFixture
{
public:
  Sulfuras() { initialQuality = 80; }

  void MakeSulfuras() { MakeItem("Sulfuras, Hand of Ragnaros"); }

  void HasNoSellInDecrease() {
    ASSERT_THAT(gildedRose.getItem(0).sellIn, Eq(initialSellIn));
  }
};

TEST_F(Sulfuras, BeforeSellDate) {
  MakeSulfuras();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

TEST_F(Sulfuras, OnSellDate) {
  initialSellIn = 0;
  MakeSulfuras();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

TEST_F(Sulfuras, AfterSellDate) {
  initialSellIn = -10;
  MakeSulfuras();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

class BackstagePass : public ItemFixture
{
public:
  void MakeBackstagePass() { MakeItem("Backstage passes to a TAFKAL80ETC concert"); }
};

TEST_F(BackstagePass, LongBeforeSellDate) {
  initialSellIn = 11;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 1);
}

TEST_F(BackstagePass, LongBeforeSellDateAtMaxQuality) {
  initialSellIn = 11;
  initialQuality = 50;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePass, MediumCloseToSellDateUpperBound) {
  initialSellIn = 10;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(BackstagePass, MediumCloseToSellDateAtMaxQualityUpperBound) {
  initialSellIn = 10;
  initialQuality = 50;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePass, MediumCloseToSellDateLowerBound) {
  initialSellIn = 6;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(BackstagePass, MediumCloseToSellDateAtMaxQualityLowerBound) {
  initialSellIn = 6;
  initialQuality = 50;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePass, VeryCloseToSellDateUpperBound) {
  initialSellIn = 5;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 3);
}

TEST_F(BackstagePass, VeryCloseToSellDateAtMaxQualityUpperBound) {
  initialSellIn = 5;
  initialQuality = 50;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePass, VeryCloseToSellDateLowerBound) {
  initialSellIn = 1;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 3);
}

TEST_F(BackstagePass, VeryCloseToSellDateAtMaxQualityLowerBound) {
  initialSellIn = 1;
  initialQuality = 50;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePass, OnSellDate) {
  initialSellIn = 0;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

TEST_F(BackstagePass, AfterSellDate) {
  initialSellIn = -10;
  MakeBackstagePass();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

class ConjuredMana : public ItemFixture
{
public:
  void MakeConjuredMana() { MakeItem("Conjured Mana Cake"); }
};

TEST_F(ConjuredMana, DISABLED_BeforeSellDate) {
  MakeConjuredMana();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(ConjuredMana, DISABLED_BeforeSellDateAtZeroQuality) {
  initialQuality = 0;
  MakeConjuredMana();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

TEST_F(ConjuredMana, DISABLED_OnSellDate) {
  initialSellIn = 0;
  MakeConjuredMana();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 4);
}

TEST_F(ConjuredMana, DISABLED_OnSellDateAtZeroQuality) {
  initialSellIn = 0;
  initialQuality = 0;
  MakeConjuredMana();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}
