import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { AuthService } from '../auth/auth.service';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.page.html',
  styleUrls: ['./settings.page.scss'],
})
export class SettingsPage implements OnInit {

  serverUsername: string;
  password: string;

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
    public router: Router,
    public authService: AuthService) { }

  ngOnInit() {
  }

}
