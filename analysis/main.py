import get_basic_info
import datagetter


def main(path: str):
    data: dict = datagetter.load(path)
    basicdata: tuple = get_basic_info.getBasic(data)
    print(
        f"You're playing as the {basicdata[0]} in the date: {basicdata[1][2]}/{basicdata[1][1]}/{basicdata[1][0]} and you have {basicdata[2]:.2f} ducats"
    )
    print(data.get("great_powers"))


main(
    "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
)
