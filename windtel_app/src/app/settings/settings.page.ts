import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { AuthService } from '../auth/auth.service';
import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.page.html',
  styleUrls: ['./settings.page.scss'],
})
export class SettingsPage implements OnInit {

  serverUsername: string;
  currentUser: User;
  password: string;

  navigate(url: string) {
    this.userService.setCurrentUser(this.currentUser);
    console.log(url);
    this.router.navigateByUrl(url);
  }

  modifySettings() {    
    this.authService.login().subscribe(() => {
      if (this.authService.isLoggedIn) {
        let redirect = this.authService.redirectUrl ? this.router.parseUrl
        (this.authService.redirectUrl) : '/tabs';

        // Redirect the user
        console.log("Modified settings");
        this.router.navigateByUrl(redirect);
      }
    });
  }

  tryModifySettings(): void {
    this.modifySettings();
  }

  constructor(
    private userService: UserService,
    public router: Router,
    public authService: AuthService) { }

  ngOnInit() {
  }

  keyDownFunction(event) {
    if(event.keyCode == 13) {
      this.tryModifySettings();
    }
  }
}
