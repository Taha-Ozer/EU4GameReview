import greatpowers
import country
import json


def aggregatePlayerAndGps(player: country.Country, gps: list[country.Country]) -> dict:
    playerDict = player.toDict()  # we convert the player to a dict
    gpsDict = greatpowers.convertGps(gps)  # same with the great powers
    combinedDict = {}  # we will aggregate them here
    combinedDict["player"] = playerDict  # player data
    combinedDict["greatPowers"] = gpsDict  # great powers data
    return combinedDict


def exportCountries(countries: dict):
    with open("data/data.json", "w") as f:
        json.dump(countries, f)  # we add the combined dict to the json file
