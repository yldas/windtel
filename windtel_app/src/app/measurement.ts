export class Measurement {

    constructor(
        public id: number,
        public liftforce: string,
        public dragfrontforce: string,
        public dragbackfroce: string,
        public leftsideforce: string,
        public rightsideforce: string,
        public windSpeed: string,
        public temperature: string,
        public humidity: string,
        public experimentid: number
    ) { }
}
