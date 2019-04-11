export class User {

    constructor(
        public id: number,
        public first: string,
        public last: string,
        public email: string,
        public vocation: string,
        public department: string,
        public institution: string,
        public city: string,
        public password: string,
        public permissions: string
    ) { }
}
