using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Bulky.DataAccess.Data;
using Bulky.Models;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace BulkyWeb.Controllers;

public class CategoryController : Controller
{
    private readonly ApplicationDbContext _db;

    public CategoryController(ApplicationDbContext db)
    {
        _db = db;
    }

    public IActionResult Index()
    {
        List<Category> objCategoryList = _db.Categories.ToList();
        return View(objCategoryList);
    }

    public IActionResult Create()
    {
        return View();
    }

    [HttpPost]
    public IActionResult Create(Category obj)
    {
        if (obj.Name == obj.DisplayOrder.ToString()) {
            ModelState.AddModelError("name", "The Display Order cannot exactly match the Name.");
        }
        if (obj.Name != null && obj.Name.ToLower() == "test")
        {
            ModelState.AddModelError("", "Test is an invalid value.");
        }
        if (ModelState.IsValid) {
            _db.Categories.Add(obj);
            _db.SaveChanges();
            TempData["success"] = "Category created successfully.";
            return RedirectToAction("Index");
        }
        return View();
    }

    public IActionResult Edit(int? id)
    {
        Category? categoryToEdit = _db.Categories.Find(id); // Only works with primary key
        if (categoryToEdit == null)
        {
            return NotFound();
        }
        return View(categoryToEdit);
    }

    [HttpPost]
    public IActionResult Edit(Category obj) {
        if (obj.Name == obj.DisplayOrder.ToString())
        {
            ModelState.AddModelError("name", "The Display Order cannot exactly match the Name.");
        }
        if (obj.Name != null && obj.Name.ToLower() == "test")
        {
            ModelState.AddModelError("", "Test is an invalid value.");
        }
        if (ModelState.IsValid)
        {
            _db.Categories.Update(obj);
            _db.SaveChanges();
            TempData["success"] = "Category updated successfully.";
            return RedirectToAction("Index");
        }
        return View();
    }

    public IActionResult Delete(int? id)
    {
        Category? categoryToDelete = _db.Categories.Find(id); // Only works with primary key
        if (categoryToDelete == null)
        {
            return NotFound();
        }
        return View(categoryToDelete);
    }

    [HttpPost, ActionName("Delete")]
    public IActionResult DeletePost(int? id)
    {
        Category? categoryToDelete = _db.Categories.Find(id); // Only works with primary key
        if (categoryToDelete == null)
        {
            return NotFound();
        }
        _db.Categories.Remove(categoryToDelete);
        _db.SaveChanges();
        TempData["success"] = "Category deleted successfully.";
        return RedirectToAction("Index");
    }
}
