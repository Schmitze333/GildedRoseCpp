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
    gildedRose.addItem(Item::CreateItem(name, initialSellIn, initialQuality));
  }

  void HasSellInDecreaseOf1() {
    HasSellInOf(initialSellIn - 1);
  }

  void HasSellInOf(const int newSellIn) {
    ASSERT_THAT(gildedRose.getItem(0)->sellIn, Eq(newSellIn));
  }

  void HasQualityOf(const int newQuality) {
    ASSERT_THAT(gildedRose.getItem(0)->quality, Eq(newQuality));
  }

  void Subject() { gildedRose.updateQuality(); }
};

class NormalItemSpec : public ItemFixture
{
public:
  void MakeNormalItemSpec() { MakeItem("NORMAL ITEM"); }
};

TEST_F(NormalItemSpec, BeforeSellDate) {
  MakeNormalItemSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 1);
}

TEST_F(NormalItemSpec, OnSellDate) {
  initialSellIn = 0;
  MakeNormalItemSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItemSpec, AfterSellDate) {
  initialSellIn = -10;
  MakeNormalItemSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(NormalItemSpec, OfZeroQuality) {
  initialQuality = 0;
  MakeNormalItemSpec();

  Subject();

  HasQualityOf(0);
}

class AgedBrieSpec : public ItemFixture
{
public:
  void MakeAgedBrieSpec() { MakeItem("Aged Brie"); }
};

TEST_F(AgedBrieSpec, BeforeSellDate) {
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 1);
}

TEST_F(AgedBrieSpec, BeforeSellDateWithMaxQuality) {
  initialQuality = 50;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(AgedBrieSpec, OnSellDate) {
  initialSellIn = 0;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(AgedBrieSpec, OnSellDateNearMaxQuality) {
  initialSellIn = 0;
  initialQuality = 49;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

TEST_F(AgedBrieSpec, OnSellDateWithMaxQuality) {
  initialSellIn = 0;
  initialQuality = 50;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

TEST_F(AgedBrieSpec, AfterSellDate) {
  initialSellIn = -10;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(AgedBrieSpec, AfterSellDateWithMaxQuality) {
  initialSellIn = -10;
  initialQuality = 50;
  MakeAgedBrieSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(50);
}

class SulfurasSpecs : public ItemFixture
{
public:
  SulfurasSpecs() { initialQuality = 80; }

  void MakeSulfurasSpecs() { MakeItem("SulfurasSpecs, Hand of Ragnaros"); }

  void HasNoSellInDecrease() {
    ASSERT_THAT(gildedRose.getItem(0)->sellIn, Eq(initialSellIn));
  }
};

TEST_F(SulfurasSpecs, BeforeSellDate) {
  MakeSulfurasSpecs();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

TEST_F(SulfurasSpecs, OnSellDate) {
  initialSellIn = 0;
  MakeSulfurasSpecs();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

TEST_F(SulfurasSpecs, AfterSellDate) {
  initialSellIn = -10;
  MakeSulfurasSpecs();

  Subject();

  HasNoSellInDecrease();
  HasQualityOf(initialQuality);
}

class BackstagePassSpec : public ItemFixture
{
public:
  void MakeBackstagePassSpec() { MakeItem("Backstage passes to a TAFKAL80ETC concert"); }
};

TEST_F(BackstagePassSpec, LongBeforeSellDate) {
  initialSellIn = 11;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 1);
}

TEST_F(BackstagePassSpec, LongBeforeSellDateAtMaxQuality) {
  initialSellIn = 11;
  initialQuality = 50;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePassSpec, MediumCloseToSellDateUpperBound) {
  initialSellIn = 10;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(BackstagePassSpec, MediumCloseToSellDateAtMaxQualityUpperBound) {
  initialSellIn = 10;
  initialQuality = 50;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePassSpec, MediumCloseToSellDateLowerBound) {
  initialSellIn = 6;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 2);
}

TEST_F(BackstagePassSpec, MediumCloseToSellDateAtMaxQualityLowerBound) {
  initialSellIn = 6;
  initialQuality = 50;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePassSpec, VeryCloseToSellDateUpperBound) {
  initialSellIn = 5;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 3);
}

TEST_F(BackstagePassSpec, VeryCloseToSellDateAtMaxQualityUpperBound) {
  initialSellIn = 5;
  initialQuality = 50;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePassSpec, VeryCloseToSellDateLowerBound) {
  initialSellIn = 1;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality + 3);
}

TEST_F(BackstagePassSpec, VeryCloseToSellDateAtMaxQualityLowerBound) {
  initialSellIn = 1;
  initialQuality = 50;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality);
}

TEST_F(BackstagePassSpec, OnSellDate) {
  initialSellIn = 0;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

TEST_F(BackstagePassSpec, AfterSellDate) {
  initialSellIn = -10;
  MakeBackstagePassSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

class ConjuredManaSpec : public ItemFixture
{
public:
  void MakeConjuredManaSpec() { MakeItem("Conjured Mana Cake"); }
};

TEST_F(ConjuredManaSpec, BeforeSellDate) {
  MakeConjuredManaSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 2);
}

TEST_F(ConjuredManaSpec, BeforeSellDateAtZeroQuality) {
  initialQuality = 0;
  MakeConjuredManaSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}

TEST_F(ConjuredManaSpec, OnSellDate) {
  initialSellIn = 0;
  MakeConjuredManaSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(initialQuality - 4);
}

TEST_F(ConjuredManaSpec, OnSellDateAtZeroQuality) {
  initialSellIn = 0;
  initialQuality = 0;
  MakeConjuredManaSpec();

  Subject();

  HasSellInDecreaseOf1();
  HasQualityOf(0);
}
