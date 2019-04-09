import { Component, OnInit } from '@angular/core';

import { User } from '../user';
import { UserService } from '../user.service';
import { modelGroupProvider } from '@angular/forms/src/directives/ng_model_group';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

  model = new User(1, 'Misael', 'misael.valentin@upr.edu', '12345678', 'Researcher');

  registered_users: User[];

  public currentUser: User;

  submitted = false;

  tryLogin() {
    this.currentUser = new User(1, 'Misael', this.model.email, this.model.password, 'Researcher');
    this.onSubmit();
  }

  onSubmit() {
    this.submitted = true;
    this.userService.setCurrentUser(this.currentUser);
  }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

  getUsers(): void {
    this.userService.getUsers()
        .subscribe(registered_users => this.registered_users = registered_users);
  }

  constructor(private userService: UserService) { }

  ngOnInit() {
    this.getUsers();
  }

}
