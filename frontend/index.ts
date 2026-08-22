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
