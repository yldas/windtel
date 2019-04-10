import { Component, OnInit } from '@angular/core';

import { User } from '../user';
import { UserService } from '../user.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

  model = new User(1, 'Misael', 'misael.valentin@upr.edu', '12345678', 'Researcher');

  registered_users: User[];

  currentUser: User;

  submitted = false;

  tryLogin() {
    this.userService.getUser(this.model.email)
        .subscribe(currentUser => this.currentUser = currentUser);
    //this.currentUser = new User(1, 'Misael', this.model.email, this.model.password, 'Researcher');
    this.onSubmit();
  }

  onSubmit() {
    this.submitted = true;
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
