import { Component, OnInit } from '@angular/core';

import { User } from '../user';
import { UserService } from '../user.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

  model = new User(1, 'Misael', 'Valentin', 'misael.valentin@upr.edu', 'Student', 'ICOM', 'UPRM', 'Aguadilla', '12345678', 'Researcher');

  registered_users: User[];

  currentUser: User;

  submitted = false;

  tryLogin() {
    //this.getRegisteredUsers();
    this.userService.getUser(this.model.email, this.model.password, this.registered_users)
        .subscribe(currentUser => this.currentUser = currentUser);
    this.onSubmit();
  }

  onSubmit() {
    this.submitted = true;
    console.log(this.currentUser.email);
    this.userService.setCurrentUser(this.currentUser);
  }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

  getRegisteredUsers(): void {
    this.userService.getRegisteredUsers()
        .subscribe(registered_users => this.registered_users = registered_users);
  }

  constructor(private userService: UserService) { }

  ngOnInit() {
    this.getRegisteredUsers();
  }

}
