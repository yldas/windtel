import { InMemoryDbService } from 'angular-in-memory-web-api';
import { User } from './user';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class InMemoryDataService implements InMemoryDbService {
  createDb() {
    const users = [
      { id: 1, name: 'Misael', email: 'misael.valentin', password: '12345678', permissions: 'Researcher' },
      { id: 2, name: 'Raúl', email: 'raul.zapata', password: '12345678', permissions: 'Administrator' },
      { id: 3, name: 'Ivan', email: 'ivan.santiago', password: '12345678', permissions: 'Technician' }
    ];
    console.log('Created DB');
    return {users};
  }

  // Overrides the genId method to ensure that a user always has an id.
  // If the users array is empty,
  // the method below returns the initial number (1).
  // if the users array is not empty, the method below returns the highest
  // user id + 1.
  genId(users: User[]): number {
    return users.length > 0 ? Math.max(...users.map(user => user.id)) + 1 : 1;
  }
}