import get_basic_info
import datagetter
import localisation
import country
import greatpowers


def main(path: str):
    localisations: dict = localisation.loadLocalisations(
        "E:\\Europa Universalis 4\\localisation\\countries_l_english.yml"
    )
    data: dict = datagetter.load(path)
    basicdata: tuple = get_basic_info.getBasic(data)
    print(
        f"You're playing as the {basicdata[0]} in the date: {basicdata[1][2]}/{basicdata[1][1]}/{basicdata[1][0]}"
    )
    gps = greatpowers.getGreatPowers(data, localisations)
    for entry in gps:
        print(entry)


main(
    "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
)
