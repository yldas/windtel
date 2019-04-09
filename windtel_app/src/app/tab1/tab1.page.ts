import { Component } from '@angular/core';

import { LoginPage } from '../login/login.page'; 
import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-tab1',
  templateUrl: 'tab1.page.html',
  styleUrls: ['tab1.page.scss']
})
export class Tab1Page {

  constructor(private userService: UserService) { }

  getCurrentUser() {
    return this.userService.getCurrentUser().email;
  }

  ngOnInit() {
  }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

}
