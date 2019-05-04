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

  users: User[];
  deleted_users: User[] = [];
  modified_users: User[] = [];
  modified: boolean = false;
  currentUser: User;
  permissions: string;

  tryModifyUsers() {
    var j;
    for (j = 0; j < this.modified_users.length; j++) {
      console.log(this.modified_users[j].email);
      this.userService.changePermissions(this.modified_users[j]).subscribe();
    }
    var i;
    for (i = 0; i < this.deleted_users.length; i++) {
      console.log(this.deleted_users[i].email);
      this.userService.deleteUser(this.deleted_users[i]).subscribe();
    }
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

  changePermissions(event: any, selected_user: User) {
    let new_permissions: any = event.target.value;
    console.log("Modifying permissions...");
    console.log(new_permissions);
    console.log(selected_user.email);
    selected_user.permissions = new_permissions;
    this.modified_users.push(selected_user);
  }

  getRegisteredUsers(): void {
    this.userService.getRegisteredUsers()
        .subscribe(users => {
          this.users = users;
        });
  }

  delete(user: User) {
    this.users = this.users.filter(u => u !== user);
    this.deleted_users.push(user);
  }

  getCurrentUser() {
    this.currentUser = this.userService.getCurrentUser();
    this.permissions = this.currentUser.permissions;
  }

  constructor(
    public authService: AuthService,
    public router: Router,
    private userService: UserService) { }

  ngOnInit() {
    this.getCurrentUser();
    this.getRegisteredUsers();
  }

  navigate(url: string) {
    //this.userService.setCurrentUser(this.currentUser);
    console.log(url);
    this.router.navigateByUrl(url);
  }
}
