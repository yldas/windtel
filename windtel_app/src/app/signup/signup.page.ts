import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User } from '../user';
import { UserService } from '../user.service';
import { AuthService } from '../auth/auth.service';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.page.html',
  styleUrls: ['./signup.page.scss'],
})
export class SignupPage implements OnInit {

  email: string;
  password: string;
  firstName: string;
  lastName: string;
  vocation: string;
  department: string;
  institution: string;
  city: string;

  userExists: boolean = false;
  registered_users: User[];
  newUser: User;
  taken: boolean = false;

  tryRegister(): void {
    this.newUser = this.registered_users.find(newUser => newUser.email === this.email);
    if (this.newUser) {
      this.taken = true;
    } else {
    this.userService.registerUser(
      { email: this.email, password: this.password, first: this.firstName, last: this.lastName,
        vocation: this.vocation, institution: this.institution, city: this.city, permissions: 'Researcher' } as User )
        .subscribe(user => { 
          this.registered_users.push(user);
          console.log("Registration successful");
        })
        this.register();
      }
  }

  register() {    
    this.authService.login().subscribe(() => {
      if (this.authService.isLoggedIn) {
        let redirect = this.authService.redirectUrl ? this.router.parseUrl
        (this.authService.redirectUrl) : '/';

        // Redirect the user
        this.router.navigateByUrl(redirect);
        this.taken = false;
      }
    });
  }

  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

  getRegisteredUsers(): void {
    this.userService.getRegisteredUsers()
        .subscribe(registered_users => this.registered_users = registered_users);
  }

  constructor(
    public authService: AuthService,
    public router: Router,
    private userService: UserService) { }

  ngOnInit() {
    this.getRegisteredUsers();
  }

  navigate(url: string) {
    console.log(url);
    this.router.navigateByUrl(url);
  }

  keyDownFunction(event) {
    if(event.keyCode == 13) {
      this.tryRegister();
    }
  }
}
