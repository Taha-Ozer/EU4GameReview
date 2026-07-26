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

    def __str__(self):
        return f"===== {self.name} =====\n\n===Economy===\n -Treasury: {self.treasury}\n -Income: {self.estimated_monthly_income}\n -Development: {self.development}\n===Military===\n -Regiments: {self.regiment_count}\n -Ships: {self.ship_count}\n -Manpower: {self.manpower}\n\n"

    def toDict(
        self,
    ) -> (
        dict
    ):  # This function is to convert a country to a dictionary of the self variables
        countryDict = {}
        countryDict["tag"] = self.tag
        countryDict["name"] = self.name
        countryDict["treasury"] = self.treasury
        countryDict["estimated_monthly_income"] = self.estimated_monthly_income
        countryDict["manpower"] = self.manpower
        countryDict["regiment_count"] = self.regiment_count
        countryDict["ship_count"] = self.ship_count
        countryDict["development"] = self.development
        return countryDict


def getCountry(tag: str, data: dict, localisations: dict) -> Country:
    country_data = data["countries"][tag]  # the data is from the tag we are searching
    # === Call all of the gathering functions ===
    countryName = getCountryLocalisation(tag, localisations)
    countryTreasury = getCountryTreasury(country_data)
    countryIncome = getCountryIncome(country_data)
    countryManpower = getCountryManpower(country_data)
    countryRegimentCount = getCountryArmySize(country_data)
    countryShipCount = getCountryNavySize(country_data)
    countryDev = getCountryDevelopment(country_data)
    # make a Country object and return it
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


def getCountryLocalisation(tag: str, localisations: dict) -> str:
    return localisations[tag]  # we return the localisation from the dict


def getCountryTreasury(country_data: dict) -> float:
    return country_data.get(
        "treasury", 0.0
    )  # we get the treasury otherwise just return 0


def getCountryIncome(country_data: dict) -> float:
    return country_data.get(
        "estimated_monthly_income", 0.0
    )  # return income default to 0


def getCountryManpower(country_data: dict) -> int:
    return country_data.get("manpower", 0)  # return manpower default to 0


def getCountryArmySize(country_data: dict) -> int:
    country_armies = country_data.get(
        "army", []
    )  # we get the "army" key and if it doesn't exist we return an empty list
    if isinstance(country_armies, dict):
        country_armies = [country_armies]
    total_regiments = 0  # we init the total regiments at 0

    for army in country_armies:
        if "regiment" not in army:  # if it doesnt contain "regiment" we can continue
            continue
        for _ in army["regiment"]:
            total_regiments += 1  # increment tota regiments
    return total_regiments  # return total regiments (0 if we returned an empty list)


def getCountryNavySize(country_data: dict) -> int:
    country_navies = country_data.get(
        "navy", []
    )  # same as army we get navy, if it doesnt exist return empty list
    if isinstance(country_navies, dict):
        country_navies = [country_navies]
    total_ships = 0  # init at 0

    # logic idem army
    for fleet in country_navies:
        if "ship" not in fleet:
            continue
        for _ in fleet["ship"]:
            total_ships += 1
    return total_ships  # return total ships


def getCountryDevelopment(country_data: dict) -> int:
    return country_data.get(
        "development", 0
    )  # we return the development, if an error occurs we default to 0
