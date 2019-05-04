import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-diagnostics',
  templateUrl: './diagnostics.page.html',
  styleUrls: ['./diagnostics.page.scss'],
})
export class DiagnosticsPage implements OnInit {

  currentUser: User;

  constructor(
    private userService: UserService,
    public router: Router) { }

    navigate(url: string) {
      this.userService.setCurrentUser(this.currentUser);
      console.log(url);
      this.router.navigateByUrl(url);
    }

  ngOnInit() {
  }

}
