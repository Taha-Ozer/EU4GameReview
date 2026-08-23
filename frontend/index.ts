interface Country {
    // We need a Country interface to be able to represent our countries in the GP list and ourselves.
    // same fields as the Country class in the pythonfiles
    tag: string;
    name: string;
    treasury: number;
    estimated_monthly_income: number;
    manpower: number;
    regiment_count: number;
    ship_count: number;
    development: number;

};

interface RawBaseData {
    // We use a top level Raw interface that has the player and the GPs
    player: Country;
    greatPowers: Country[];

};

enum ElementType {
    // an enum class to be able to classify elementtypes
    NAME,
    DEV,
    TREASURY,
    INCOME,
    MANPOWER,
    REGIMENTS,
    SHIPS
};

async function fetchFile(path: string): Promise<RawBaseData | null> {

    try {
        const response = await fetch(path); // we get the file
        if (!response.ok) {
            throw new Error(`Error: ${response.status}`); // if response is bad we throw error
        }
        const data: RawBaseData = await response.json(); // cast it into a RawBaseData
        return data;
    }
    catch (error) {
        console.error(error); // if fail: we show the error and return a null
        return null;
    }

}

// we add an eventlistener to load the data when the page is laoded
document.addEventListener('DOMContentLoaded', async () => {
    let data: RawBaseData | null = await fetchFile("../data/data.json"); // we fetch the file
    if (!data) {

        console.log(`Couldn't read the JSON data file`); // log an error if there is no data
    }
    else {
        const name: HTMLElement | null = document.getElementById("playerName");
        if (!name) {

            console.log(`Couldn't fetch name`);
        }
        else {
            populateLeftBar(data.player); // we populate the data of the player.
        }
    }
});

function populateLeftBar(player: Country): void {

    // we populate the left bar with every needed field
    putValueInElement("playerName", player, ElementType.NAME);
    putValueInElement("devValue", player, ElementType.DEV);
    putValueInElement("treasuryValue", player, ElementType.TREASURY);
    putValueInElement("incomeValue", player, ElementType.INCOME);
    putValueInElement("manpowerValue", player, ElementType.MANPOWER);
    putValueInElement("regimentValue", player, ElementType.REGIMENTS);
    putValueInElement("shipValue", player, ElementType.SHIPS);
}

function putValueInElement(element: string, player: Country, type: ElementType): void {
    // first get the element specified by the parameter
    const htmlvalue: HTMLElement | null = document.getElementById(element);
    if (!htmlvalue) {
        console.log(`Value couldn't be fetched!\n`); // if not fetched
    }
    else {
        // according to the type we say, we put the value in the html textcontent.
        // if needed we convert the value to a string with a .toString();
        switch (type) {
            case ElementType.NAME:
                htmlvalue.textContent = player.name;
                break;
            case ElementType.DEV:
                htmlvalue.textContent = player.development.toFixed(0).toString();
                break;
            case ElementType.INCOME:
                htmlvalue.textContent = player.estimated_monthly_income.toFixed(2).toString();
                break;
            case ElementType.TREASURY:
                htmlvalue.textContent = player.treasury.toFixed(2).toString();
                break;
            case ElementType.MANPOWER:
                htmlvalue.textContent = player.manpower.toFixed(2).toString().concat('k');
                break;
            case ElementType.REGIMENTS:
                htmlvalue.textContent = player.regiment_count.toFixed(0).toString();
                break;
            case ElementType.SHIPS:
                htmlvalue.textContent = player.ship_count.toFixed(0).toString();
                break;

        }
    }
}
