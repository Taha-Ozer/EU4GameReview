import country


def getGreatPowers(data: dict, localisations: dict) -> list:
    great_powers_og: dict = data.get("great_powers", {})
    great_powers: dict = great_powers_og.get("original", {})
    result: list = []
    for entry in great_powers:
        result.append(country.getCountry(entry.get("country"), data, localisations))
    return result
