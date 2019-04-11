import { Component, OnInit } from '@angular/core';

import { User } from '../user';
import { UserService } from '../user.service';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.page.html',
  styleUrls: ['./signup.page.scss'],
})
export class SignupPage implements OnInit {

  model = new User(1, 'Misael', 'Valentin', 'misael.valentin@upr.edu', '12345678', 'Researcher');

  registered_users: User[];

  currentUser: User;

  submitted = false;

  tryRegister() {
    this.currentUser = new User(1, this.model.first, this.model.last, this.model.email, this.model.password, 'Researcher');
    this.userService.registerUser(this.currentUser);
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
