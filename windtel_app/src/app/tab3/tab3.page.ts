import { Component } from '@angular/core';

import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-tab3',
  templateUrl: 'tab3.page.html',
  styleUrls: ['tab3.page.scss']
})
export class Tab3Page {

  currentUser: User;
  permissions: string;
  
  constructor(private userService: UserService) { }

  getCurrentUser() {
    this.currentUser = this.userService.getCurrentUser();
    this.permissions = this.currentUser.permissions;
  }

}
