// The interface we use to build our country datatype
export interface Country{
    tag: string,
    name: string,
    treasury: number,
    estimated_monthly_income: number,
    manpower: number,
    regiment_count: number,
    ship_count: number,
    development: number
}


// We will use this interface to extract the player and gp data
export interface RawBaseData{
    player: Country,
    greatPowers: Country[]
}


// An enum to be able to classify elements we will use
export enum ElementType{
    NAME,
    DEV,
    TREASURY,
    INCOME,
    MANPOWER,
    REGIMENTS,
    SHIPS
}