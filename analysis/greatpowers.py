import country


def getGreatPowers(data: dict, localisations: dict) -> list:
    great_powers_og: dict = data.get(
        "great_powers", {}
    )  # we get the great_powers key's value
    great_powers: dict = great_powers_og.get(
        "original", {}
    )  # that value is "original" so we get the value of "original"
    result: list = []  # this will be our result list
    for entry in great_powers:  # for every GP entry in the great_powers dict
        result.append(
            country.getCountry(entry.get("country"), data, localisations)
        )  # we add it to the list as a country
    return result


def convertGps(
    gplist: list[country.Country],
) -> (
    list
):  # This function is to convert a list of great powers (country) to a list of great powers (dicts)
    gpdlist: list = []  # Great Powers Dictionary List
    for gp in gplist:
        gpdlist.append(gp.toDict())  # we append every new dict to our returnlist
    return gpdlist
