import { type Country, type RawBaseData, ElementType } from "./types.js";


// The function to read a specified file and return the raw base data object
export async function readData(path: string): Promise<RawBaseData | null>{
    try{
        // We try to get the file from the path
        const response = await fetch(path);
        if (!response.ok){
            throw new Error("Error while fetching file\n"); // if the response is not ok, we throw an error
        }
        // We cast the rawbasedata and return it
        const data: RawBaseData = await response.json();
        return data;
    }
    catch (error){
        // if we can't do it, we throw an error and return null
        console.error(error);
        return null;
    }
}