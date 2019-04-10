import { Component } from '@angular/core';

import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-tab1',
  templateUrl: 'tab1.page.html',
  styleUrls: ['tab1.page.scss']
})
export class Tab1Page {

  currentUser: User;

  constructor(private userService: UserService) { }

  getCurrentUser() {
    this.currentUser = this.userService.getCurrentUser();
  }

  ngOnInit() { }

  // TODO: Remove this when we're done
  get diagnostic() { return JSON.stringify(this.userService.getCurrentUser()); }

}
