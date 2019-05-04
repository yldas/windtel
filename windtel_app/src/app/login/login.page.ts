import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User } from '../user';
import { UserService } from '../user.service';
import { AuthService } from '../auth/auth.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

  email: string;
  password: string;
  registered_users: User[];
  incorrectLogin: boolean = false;
  currentUser: User;

  tryLogin() {
    this.userService.getRegisteredUsers()
        .subscribe(registered_users => {
          this.registered_users = registered_users;
          console.log("Fetched users");
          this.currentUser = this.userService.getUser(this.email, this.password, this.registered_users);
          if (this.currentUser) {
            this.userService.setCurrentUser(this.currentUser);
            this.login();
          } else {
            this.incorrectLogin = true;
          }
        })
      }

  login() {    
    this.authService.login().subscribe(() => {
      if (this.authService.isLoggedIn) {
        let redirect = this.authService.redirectUrl ? this.router.parseUrl
        (this.authService.redirectUrl) : '/tabs';

        // Redirect the user
        console.log("Logged in");
        this.router.navigateByUrl(redirect);
        this.incorrectLogin = false;
      }
    });
  }

  getRegisteredUsers(): void {
    this.userService.getRegisteredUsers()
        .subscribe(registered_users => {
          this.registered_users = registered_users;
          console.log("Fetched users");
        })
  }

  constructor(
    public authService: AuthService,
    public router: Router,
    private userService: UserService) { }

  ngOnInit() {
    this.getRegisteredUsers();
  }

  keyDownFunction(event) {
    if(event.keyCode == 13) {
      this.tryLogin();
    }
  }
}
