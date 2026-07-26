import country
import localisation


def getBasic(data: dict) -> tuple:
    playerTag: str = data["player"]
    date: tuple = data["date"]
    player: str = data["displayed_country_name"]
    return (player, date, playerTag)


def getPlayer(data: dict, localisations: dict) -> country.Country:

    return country.getCountry(
        data["player"], data, localisations
    )  # we get the Country object of the player
