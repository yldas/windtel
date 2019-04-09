import { Injectable } from '@angular/core';

import { Observable, of } from 'rxjs';

import { User } from './user';
import { USERS } from './mock-users';

@Injectable({
  providedIn: 'root'
})
export class UserService {

  current_user: User;

  constructor() { }

  getUsers(): Observable<User[]> {
    return of(USERS);
  }

  setCurrentUser(current_user: User) {
    this.current_user = current_user;
  }

  getCurrentUser(): User {
    return this.current_user;
  }
}
