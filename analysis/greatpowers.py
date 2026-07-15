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
