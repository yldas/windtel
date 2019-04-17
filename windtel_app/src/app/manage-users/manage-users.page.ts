import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { AuthService } from '../auth/auth.service';
import { User } from '../user';
import { UserService } from '../user.service';

@Component({
  selector: 'app-manage-users',
  templateUrl: './manage-users.page.html',
  styleUrls: ['./manage-users.page.scss'],
})
export class ManageUsersPage implements OnInit {

  users: User[]
  modified: boolean = false;

  tryModifyUsers() {
    this.modifyUsers();
    this.modified = true;
  }

  modifyUsers() {    
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

  getRegisteredUsers(): void {
    this.userService.getRegisteredUsers()
        .subscribe(users => this.users = users);
  }

  delete(user: User) {
    this.users = this.users.filter(u => u !== user);
  }

  constructor(
    public authService: AuthService,
    public router: Router,
    private userService: UserService) { }

  ngOnInit() {
    this.getRegisteredUsers();
  }

}
