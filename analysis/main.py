import get_basic_info
import datagetter
import localisation
import country
import greatpowers
import jsonexport


def main(path: str):
    localisations: dict = localisation.loadLocalisations(
        "E:\\Europa Universalis 4\\localisation\\countries_l_english.yml"
    )
    data: dict = datagetter.load(path)
    gps = greatpowers.getGreatPowers(data, localisations)
    player = get_basic_info.getPlayer(data, localisations)
    aggregated = jsonexport.aggregatePlayerAndGps(player, gps)
    jsonexport.exportCountries(aggregated)


main(
    "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
)
