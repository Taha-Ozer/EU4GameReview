class Country:  # Country class to visualize countries
    # The data we will store inside this will vary
    # At the early stages I am using these
    def __init__(
        self,
        tag: str,
        name: str,
        treasury: float,
        estimated_monthly_income: float,
        manpower: int,
        regiment_count: int,
        ship_count: int,
        development: int,
    ):
        self.tag = tag
        self.name = name
        self.treasury = treasury
        self.estimated_monthly_income = estimated_monthly_income
        self.manpower = manpower
        self.regiment_count = regiment_count
        self.ship_count = ship_count
        self.development = development


def getCountry(tag: str, data: dict, localisations: dict) -> Country:
    country_data = data["countries"][tag]
    countryName = localisations[tag]
    countryTreasury = country_data["treasury"]
    countryIncome = country_data["estimated_monthly_income"]
    countryManpower = country_data["manpower"]
    countryRegimentCount = analyze_army(country_data["army"])
    countryShipCount = analyze_navy(country_data["navy"])
    countryDev = country_data["development"]
    return Country(
        tag,
        countryName,
        countryTreasury,
        countryIncome,
        countryManpower,
        countryRegimentCount,
        countryShipCount,
        countryDev,
    )


def analyze_army(country_armies: dict) -> int:
    total_raw_regiments = 0

    for army in country_armies:
        if "regiment" not in army:
            continue

        for _ in army["regiment"]:
            total_raw_regiments += 1

    return total_raw_regiments


def analyze_navy(country_navies: dict) -> int:
    total_raw_ships = 0

    for fleet in country_navies:
        if "ship" not in fleet:
            continue

        for _ in fleet["ship"]:
            total_raw_ships += 1

    return total_raw_ships
