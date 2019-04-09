import { Component, OnInit } from '@angular/core';

import { User } from '../user';
import { modelGroupProvider } from '@angular/forms/src/directives/ng_model_group';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

  model = new User(1, 'Misael', 'misael.valentin@upr.edu', '12345678', 'Researcher');

  currentUser: User;

  submitted = false;

  tryLogin() {
    this.currentUser = new User(1, 'Misael', this.model.email, this.model.password, 'Researcher');
    this.onSubmit();
  }

  onSubmit() { this.submitted = true; }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.currentUser); }

  constructor() { }

  ngOnInit() {
  }

}
