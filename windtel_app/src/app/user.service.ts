import { Injectable } from '@angular/core';

import { Observable, of } from 'rxjs';

import { User } from './user';
import { USERS } from './mock-users';
import { MessageService } from './message.service';

@Injectable({
  providedIn: 'root'
})
export class UserService {

  current_user: User;

  constructor(private messageService: MessageService) { }

  getRegisteredUsers(): Observable<User[]> {
    this.messageService.add('UserService: fetched users');
    return of(USERS);
  }

  setCurrentUser(current_user: User) {
    this.current_user = current_user;
  }

  getCurrentUser(): User {
    return this.current_user;
  }

  getUser(email: string): Observable<User> {
    return of (USERS.find(current_user => current_user.email === email));
  }
}
