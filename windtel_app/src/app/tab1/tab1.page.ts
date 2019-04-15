import { Component } from '@angular/core';
import { Router } from '@angular/router';

import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-tab1',
  templateUrl: 'tab1.page.html',
  styleUrls: ['tab1.page.scss']
})
export class Tab1Page {

  currentUser: User;
  permissions: string;

  constructor(
    public router: Router,
    private userService: UserService) { }

  navigate() {
    this.userService.setCurrentUser(this.currentUser);
    this.router.navigateByUrl("settings");
  }

  getCurrentUser() {
    this.currentUser = this.userService.getCurrentUser();
    this.permissions = this.currentUser.permissions;
  }

  ngOnInit() {
    console.log("Trying to get current user...");
    this.getCurrentUser();
  }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

}
