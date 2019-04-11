import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { catchError, map, tap } from 'rxjs/operators';

import { User } from './user';
import { MessageService } from './message.service';

const httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable({
  providedIn: 'root'
})
export class UserService {

  current_user: User;
  private usersUrl = 'api/users';   // URL to web api

  registeredUsers: User[];

  constructor(
    private http: HttpClient,
    private messageService: MessageService) { }

  getRegisteredUsers(): Observable<User[]> {
    return this.http.get<User[]>(this.usersUrl);
  }

  setCurrentUser(current_user: User) {
    this.current_user = current_user;
  }

  getCurrentUser(): User {
    return this.current_user;
  }

  getUser(email: string, password: string, registeredUsers: User[]): Observable<User> {
    this.current_user = registeredUsers.find(current_user => current_user.email === email && current_user.password == password); 
    if (this.current_user) {
      return of(this.current_user);
    }
  }

  /*
  getUserOld(email: string): Observable<User> {
    return of (USERS.find(current_user => current_user.email === email));
  }
  */

  registerUser(user: User): Observable<any> {
    return this.http.post(this.usersUrl, user, httpOptions).pipe(
      tap((newUser: User) => this.log(`registered user id=${newUser.id}`)),
      catchError(this.handleError<User>('registerUser'))
    );
  }

  deleteUser(user: User | number): Observable<User> {
    const id = typeof user === 'number' ? user: user.id;
    const url = `${this.usersUrl}/${id}`;

    return this.http.delete<User>(url, httpOptions).pipe(
      tap(_ => this.log(`deleted user id=${id}`)),
      catchError(this.handleError<User>('deleteUser'))
    );
  }

  /** Log a UserService message with the MessageService */
  private log(message: string) {
  this.messageService.add(`UserService: ${message}`);
  }

  /**
   * Handle Http operation that failed.
   * Let the app continue.
   * @param operation - name of the operation that failed
   * @param result - optional value to return as the observable result
   */
    private handleError<T> (operation = 'operation', result?: T) {
      return (error: any): Observable<T> => {
    
    // TODO: send the error to remote logging infrastructure
    console.log("There was an error!");
    console.error(error); // log to console instead
    
    // TODO: better job of transforming error for user consumption
    this.log(`${operation} failed: ${error.message}`);
    
    // Let the app keep running by returning an empty result.
    return of(result as T);
    };
  }
}
