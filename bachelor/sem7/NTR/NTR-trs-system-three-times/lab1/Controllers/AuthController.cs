using System;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;

using lab1.Models.Repositories;
using lab1.Models.ViewModel;

using lab1.Controllers.Common;

namespace lab1.Controllers
{
    public class AuthController : Controller
    {

        public IActionResult Index(string msg = "")
        {
            var login = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if(login != null){
                return _handleSuccess(login);
            }
            var users = _repo.GetAllUsers();
            var usersWithMsg = new UsersWithMessage(users, msg);
            return View("Index", usersWithMsg);
        }
        public IActionResult Login(string login)
        {
            var userOpt = _repo.GetUser(login);

            return userOpt.IsNone ? _indexViewWithMsg("Such user does not exist!") : _handleSuccess(login);
        }

        [HttpPost]
        public IActionResult Register(string login)
        {
            if (login == null)
                return _indexViewWithMsg("Invalid login!");

            var userOpt = _repo.CreateUser(login);
            return userOpt.IsNone ? _indexViewWithMsg("Such user already exists!") : _handleSuccess(login);
        }

        public IActionResult Logout()
        {
            if (this.HttpContext.Session.GetString(Constants.SessionKeyName) != null)
            {
                this.HttpContext.Session.Remove(Constants.SessionKeyName);
                return _indexViewWithMsg("Succesful logout");
            }
            else
            {
                return _indexViewWithMsg();
            }
        }

        public IActionResult NotLoggedIn()
        {
            return _indexViewWithMsg("You are not logged in, please do it :)");
        }

        private IActionResult _handleSuccess(string login)
        {
            this.HttpContext.Session.SetString(Constants.SessionKeyName, login);
            return RedirectToAction("MonthSummary", "Activity");
        }

        private IActionResult _indexViewWithMsg(string msg = "")
        {
            return Index(msg);
        }
        private IRepository _repo = new RepositoryJson();
    }
}