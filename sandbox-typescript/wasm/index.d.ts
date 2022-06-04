export interface STBModule{
    isitup() : void;
    dummy_vector: dummy_vector;
    dummy_data: dummy_data;
}

export interface dummy_vector {
    new(): dummy_vector;
    new(data: dummy_data): dummy_vector;
    push(data: dummy_data) : void;
    get(index: number) : number;
}

export interface dummy_data {
    new(key: string, value: number);
    key: string;
    value: number;
}

declare function STB() : Promise<STBModule>;

export default STB;